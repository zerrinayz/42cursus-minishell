/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:42:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/24 19:47:31 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_dolar(char *meta)
{
	int	i;
	int	j;

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

int	set_meta(t_program *program, char *meta)
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
void	f(t_lexer *parser_inputiz)
{
	int		i;
	char	*tmp;
	char	*parser_input;
	int		j;

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
			else if (parser_input[i] && parser_input[i] != '\"'
				&& parser_input[i] != '\'')
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

void	quote_clean(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			zi_striteri(program->parser_input[i][j], f);
		//	printf("iteri:%s",program->parser_input[i][j]->cmd);
			if (program->parser_input[i][j]->key == 5
				&& count_dolar(program->parser_input[i][j]->cmd) == 1)
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
