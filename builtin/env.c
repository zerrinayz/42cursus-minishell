/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:46:48 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/14 17:27:07 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_program *program, char **cmd)
{
	t_list *current;
	int i;
	i = 0;

	while (cmd[i] != NULL && ft_strncmp(cmd[i],
			"env", ft_strlen("env")) == 0 && cmd[i][3] == '\0')
		i++;
	if (cmd[i] == NULL)
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
		printf("env: %s No such file or directory\n", cmd[i]);
	exit(0);
}
