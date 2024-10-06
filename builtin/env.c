/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:46:48 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/05 13:42:27 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_program *program, t_lexer ***parser_input)
{
	t_list *current;
	int i;
	i = 0;
if (parser_input[0] == NULL)
		return ;
	while (parser_input[0][i] != NULL && ft_strncmp(parser_input[0][i]->cmd,
			"env", ft_strlen("env")) == 0 && parser_input[0][i]->cmd[3] == '\0')

		i++;
	if (parser_input[0][i] == NULL)
	{
		current = program->envp_list;
		while (current != NULL)
		{
				printf("%s=%s\n", (char *)current->key,
					(char *)current->content);
			
			current = current->next;
		}
	}
	else
		printf("env: %s No such file or directory\n", parser_input[0][i]->cmd);
}