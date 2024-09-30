/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:42:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/29 20:19:04 by itulgar          ###   ########.fr       */
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
	}
	return (S_Dolar);
}
int	set_redirect(char *meta)
{
	int		i;
	char	q_type;

	q_type = '\0';
	i = 0;

	while (meta[i])
	{
		if (meta[i] && (meta[i] == '\"' || meta[i] == '\''))
		{
			q_type = meta[i];
			i++;
			while (meta[i] && meta[i] != q_type)
				i++;
			if (meta[i])
				i++;
			continue ;
		}
		if (meta[i] != '\0' && (meta[i] == '<' || meta[i] == '>'
				|| (meta[i] == '>' && meta[i + 1] == '>') || (meta[i] == '<'
					&& meta[i + 1] == '<')))
		{
			return (Redirect);
		}
		i++;
	}
	return (412);
}

int	set_meta(t_program *program, char *meta)
{
	(void)program;
	if ((ft_strchr(meta, 34) == 0) && (ft_strchr(meta, 39) == 0))
	{
		// if (!ft_strncmp(meta, "<", ft_strlen(meta)))
		// 	return (Input);
		// else if (!ft_strncmp(meta, ">", ft_strlen(meta)))
		// 	return (Output);
		// else if (!ft_strncmp(meta, "<<", ft_strlen(meta)))
		// 	return (Heredoc);
		// else if (!ft_strncmp(meta, ">>", ft_strlen(meta)))
		// 	return (Append);
		if (!ft_strncmp(meta, "~", ft_strlen(meta)))
			return (Tilde);
		else if (ft_strchr(meta, 36))
			return (Dolar);
	}
	else if (ft_strchr(meta, 36))
		return (set_dolar(meta));
	if (ft_strchr(meta, '<') || ft_strchr(meta, '>'))
		return (set_redirect(meta));
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

void	dolar_handler(t_program *program, t_lexer *parser_input)
{
	char	*before_cmd;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(parser_input->cmd);
	while (parser_input->cmd[i])
	{
		before_cmd = before_dolar(parser_input, &i, 1);
		dq_dolar_env(program, parser_input, &i, before_cmd);
		if (i >= j)
			break ;
		else
		{
			j = ft_strlen(parser_input->cmd);
			i = 0;
		}
	}
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
			if (ft_strchr(program->parser_input[i][j]->cmd, 36))
				dolar_handler(program, program->parser_input[i][j]);
			printf("cmd:%d: arg:%d:%s  key:%d\n", i, j,
				program->parser_input[i][j]->cmd,
				program->parser_input[i][j]->key);
			zi_striteri(program->parser_input[i][j], f);
			j++;
		}
		i++;
	}
}
