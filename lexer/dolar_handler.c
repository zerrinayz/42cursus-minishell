/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:24:13 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/29 20:19:12 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env(char *parser_input, char quote_type)
{
	(void)quote_type;
	if (ft_strchr(parser_input, 36))
		return (0);
	return (1);
}
char	*dolar_env(t_program *program, char *parser_input)
{
	t_list	*current;

	current = program->envp_list;
	while (current)
	{
		if (!ft_strncmp(current->key, parser_input, ft_strlen(parser_input)))
		{
			return (zi_strlcpy(parser_input, current->content,
					ft_strlen(current->content)));
		}
		current = current->next;
	}
	return (NULL);
}
char	*get_env(t_program *program, char *parser_input, char c)
{
	while (program->envp_list)
	{
		if (!ft_strncmp(program->envp_list->key, parser_input,
				zi_strlen(parser_input, c, 0)))
		{
			return (zi_strlcpy(parser_input, program->envp_list->content,
					ft_strlen(program->envp_list->content)));
		}
		program->envp_list = program->envp_list->next;
	}
	return (NULL);
}

char	*before_dolar(t_lexer *parser_input, int *i, int is_in)
{
	int		len;
	char	*before_cmd;

	len = 0;
	len = zi_strlen(parser_input->cmd + *i, 36, is_in);
	before_cmd = ft_substr(parser_input->cmd, *i, len);
	while (*i < len)
		(*i)++;
	return (before_cmd);
}

void	dq_dolar_env(t_program *program, t_lexer *parser_input, int *i,
		char *before_cmd)
{
	int		start_env;
	int		env_len;
	char	*env_str;
	char	*key;
	char	*tmp;
	char	*str;
	char	*se_dolar;
	char	*after_dolar;

	env_str = NULL;
	str = NULL;
	env_len = 0;
	if (parser_input->cmd[*i] == '\"')
	{
		se_dolar = before_dolar(parser_input, i, 0);
		if (se_dolar)
		{
			before_cmd = ft_strjoin(before_cmd, se_dolar);
		}
		while (parser_input->cmd[*i] && parser_input->cmd[*i] != 36)
			(*i)++;
	}
	if (parser_input->cmd[*i] == 36)
	{
		env_len = 0;
		(*i)++;
		start_env = *i;
		while (parser_input->cmd[*i] && (ft_isalnum(parser_input->cmd[*i])
				|| ft_isalpha(parser_input->cmd[*i])))
		{
			env_len++;
			(*i)++;
		}
		env_str = ft_substr(parser_input->cmd, start_env, env_len);
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
		free(parser_input->cmd);
		parser_input->cmd = ft_strdup(tmp);
		if (before_cmd)
			free(before_cmd);
		if (env_str[0] != '\0')
			free(env_str);
		if (after_dolar)
			free(after_dolar);
		if (tmp)
			free(tmp);
	}
}
