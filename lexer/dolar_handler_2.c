/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_handler_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:24:51 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/01 19:24:53 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*env_count_str(t_lexer *parser_input, int *i)
{
	char	*env_str;
	int		env_len;
	int		start_env;

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
	return (env_str);
}
