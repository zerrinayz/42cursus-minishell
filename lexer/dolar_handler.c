/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:24:13 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/30 19:46:10 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *before_dolar(t_lexer *parser_input, int *i, int is_in)
{
	int len;
	char *before_cmd;

	len = 0;
	len = zi_strlen(parser_input->cmd + *i, 36, is_in);
	before_cmd = ft_substr(parser_input->cmd, *i, len);
	while (*i < len)
		(*i)++;
	return (before_cmd);
}
static char *after_quote(t_lexer *parser_input, char *before_cmd, int *i)
{
	char *se_dolar;

	se_dolar = before_dolar(parser_input, i, 0);
	if (se_dolar)
	{
		before_cmd = ft_strjoin(before_cmd, se_dolar);
	}
	while (parser_input->cmd[*i] && parser_input->cmd[*i] != 36)
		(*i)++;
	return (before_cmd);
}

static char *before_dolar_assign(t_program *program, t_lexer *parser_input, char *before_cmd, int *i)
{
	char *env_str;
	char *after_dolar;
	char *tmp;
	char *key;
	char *str;

	env_str = env_count_str(parser_input, i);
	after_dolar = ft_substr(parser_input->cmd, *i,
							(ft_strlen(parser_input->cmd) - *i));
	if (env_str[0] == '\0')
		tmp = ft_strjoin(before_cmd, after_dolar);
	else
	{
		key = dolar_env(program, env_str);
		if (key != NULL)
		{
			str = ft_strjoin(before_cmd, key);
			tmp = ft_strjoin(str, after_dolar);
		}
		else
			tmp = ft_strjoin(before_cmd, after_dolar);
	}
	dolar_free(env_str, after_dolar);
	return (tmp);
}

static void dq_dolar_env(t_program *program, t_lexer *parser_input, int *i,
				  char *before_cmd)
{

	char *tmp;

	if (parser_input->cmd[*i] == '\"')
		before_cmd = after_quote(parser_input, before_cmd, i);
	if (parser_input->cmd[*i] == 36)
	{

		tmp = before_dolar_assign(program, parser_input, before_cmd, i);
		free(parser_input->cmd);
		parser_input->cmd = ft_strdup(tmp);
		if (before_cmd)
			free(before_cmd);

		if (tmp)
			free(tmp);
	}
}

void dolar_handler(t_program *program, t_lexer *parser_input)
{
	char *before_cmd;
	int i;
	int j;

	i = 0;
	j = ft_strlen(parser_input->cmd);
	while (parser_input->cmd[i])
	{
		before_cmd = before_dolar(parser_input, &i, 1);
		dq_dolar_env(program, parser_input, &i, before_cmd);
		if (i >= j)
			break;
		else
		{
			j = ft_strlen(parser_input->cmd);
			i = 0;
		}
	}
}
