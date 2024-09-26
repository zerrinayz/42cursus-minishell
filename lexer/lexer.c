/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:42:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/25 19:58:50 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int set_dolar(char *meta)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (meta[i])
	{
		if (meta[i] == '\'')
		{
			i++;
			j = 0;
			while (meta[i] && meta[i] != '\'')
			{
				if (j == 0)
					j = i - 1;
				i++;
			}
			if (zi_strrchr((meta + j), 36, i - j) == 1 && meta[i] == '\0')
				return (S_Dolar);
		}
		else if (meta[i] == '\"')
		{
			i++;
			j = 0;
			while (meta[i] && meta[i] != '\"')
			{
				if (j == 0)
					j = i - 1;
				i++;
			}
			if (zi_strrchr(meta + j, 36, i - j) == 1)
				return (Dolar);
		}
		else if (meta[i] == '$')
			return (Dolar);
		i++;
		// dolarlı yer string mi değil mi diye bak
	}
	return (S_Dolar);
}

int set_meta(t_program *program, char *meta)
{
	(void)program;
	if ((ft_strchr(meta, 34) == 0) && (ft_strchr(meta, 39) == 0))
	{
		if (!ft_strncmp(meta, "<", ft_strlen(meta)))
			return (Input);
		else if (!ft_strncmp(meta, ">", ft_strlen(meta)))
			return (Output);
		else if (!ft_strncmp(meta, "<<", ft_strlen(meta)))
			return (Heredoc);
		else if (!ft_strncmp(meta, ">>", ft_strlen(meta)))
			return (Append);
		else if (!ft_strncmp(meta, "~", ft_strlen(meta)))
			return (Tilde);
		else if (ft_strchr(meta, 36))
			return (Dolar);
	}
	else if (ft_strchr(meta, 36))
		return (set_dolar(meta));
	return (412);
}
void f(t_lexer *parser_inputiz)
{
	int i;
	char *tmp;
	char *parser_input;
	int j;

	parser_input = parser_inputiz->cmd;
	tmp = (char *)malloc((ft_strlen(parser_input) + 1) * sizeof(char));
	if (!tmp)
	{
		printf("Bellek ayırma hatası!\n");
	}
	else
	{
		j = 0;
		i = 0;
		while (parser_input[i] != '\0')
		{
			if (parser_input[i] == '\'')
			{
				i++;
				while (parser_input[i] != '\'' && parser_input[i] != '\0')
				{
					tmp[j] = parser_input[i];
					i++;
					j++;
				}
			}
			else if (parser_input[i] == '\"')
			{
				i++;
				while (parser_input[i] != '\"' && parser_input[i] != '\0')
				{
					tmp[j] = parser_input[i];
					i++;
					j++;
				}
			}
			else if (parser_input[i] && parser_input[i] != '\"' && parser_input[i] != '\'')
			{
				tmp[j] = parser_input[i];
				j++;
			}
			if (parser_input[i])
				i++;
		}
		tmp[j] = '\0';
		parser_inputiz->cmd = zi_strlcpy(parser_input, tmp,
										 ft_strlen(parser_input));
	}
	free(tmp);
}

int d_count_cmd(t_program *program, char *p_input)
{
	char q_type;
	int i;
	int count;

	(void)program;
	i = 0;
	count = 0;
	while (p_input[i])
	{
		if (p_input[i] == 36)
		{
			i++;
			while (p_input[i] && (p_input[i] != '\'' && p_input[i] != '\"' && p_input[i] != 36))
				i++;
			if (p_input[i] == '\0' || p_input[i] == 36)
				count++;
			if (p_input[i] == '\'' || p_input[i] == '\"')
			{
				q_type = p_input[i];
				if (!is_env(p_input + i + 1, q_type))
					count++;
			}
		}
		else if (p_input[i] == '\'' || p_input[i] == '\"')
		{
			q_type = p_input[i];
			if (!is_env(p_input + i, q_type))
				count++;
			i++;
			while (p_input[i] && (p_input[i] != q_type))
				i++;
			i++;
		}
		else if (p_input[i])
			i++;
	}
	return (count);
}

static int is_multi_dolar(char *p_inputiz, char q_type)
{
	int count = 0;
	while (p_inputiz && *p_inputiz != q_type)
	{
		if (*p_inputiz == 36)
			count++;
		p_inputiz++;
	}
	return count;
}
void dolar_mix_assign(t_program *program, t_lexer *parser_input)
{
	char *p_inputiz;

	char q_type;
	int i = 0;
	int j = 0;
	int k = 0;
	p_inputiz = parser_input->cmd;
	program->d_cmd = (char **)malloc(sizeof(char *) * (d_count_cmd(program, p_inputiz) + 1));
	if (!program->d_cmd)
		error_message("memory allocation");
	while (p_inputiz[i])
	{
		if (p_inputiz[i] == '\'' || p_inputiz[i] == '\"')
		{
			q_type = p_inputiz[i];
			
			if (is_multi_dolar(p_inputiz + i, q_type) > 1)
			{
				j=0;
				program->d_cmd[k][j].cmd = p_inputiz[i];
				i++;
				j++;
				while (p_inputiz[i] && p_inputiz[i] != q_type)
				{
					program->d_cmd[k][j].cmd = p_inputiz[i];
					j++;
					i++;
				}
			}
			k++;
				//a"'$HOME'$HOME"$H'O'ME"$HOME"
				// 23.home 'un nasıl durduğunu anlamak için tırnak ve sonrasında dolar varsa yeni bir 
				//dolara geçtin daha doldurma dur de
		
		}else if(p_inputiz[i]==36)
		{
			j=0;
			while (p_inputiz[i] && p_inputiz[i] != 36)
				{
					program->d_cmd[k][j].cmd = p_inputiz[i];
					j++;
					if(p_inputiz[i]=='\'' || p_inputiz[i]=='\'')
					i++;
				}
				k++;
		}
		else {
			program->d_cmd[k][j].cmd = p_inputiz[i];
			i++;
			j++;
		}

	}

	// while (a <= d_count(program, p_inputiz))
	// {
	// 	if (assign_dolar())
	// 		tmp = loc_dolar();
	// 	tmp2 = parser_input[i][j].cmd;
	// }
}
void quote_clean(t_program *program)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (program->parser_input[i][j]->key == 5 && count_dolar(program->parser_input[i][j]->cmd) > 1)
				dolar_mix_assign(program, program->parser_input[i][j]);
			zi_striteri(program->parser_input[i][j], f);
			// printf("iteri:%s",program->parser_input[i][j]->cmd);
			if (program->parser_input[i][j]->key == 5 && count_dolar(program->parser_input[i][j]->cmd) == 1)
				loc_dolar(program, program->parser_input[i][j]);

			printf("-----------command:%d: arg:%d:%s  key:%d\n", i, j,
				   program->parser_input[i][j]->cmd,
				   program->parser_input[i][j]->key);
			j++;
		}
		i++;
	}
}

//  echo "$HOME"'$HOME''"$HOME"' birden fazla dolarlı ise dolar olarak
// setle . tırnak temizlerken birden fazla varsa içini tek tek temizle(execde)
