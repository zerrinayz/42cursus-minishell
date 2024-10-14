/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:36:01 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/14 16:22:35 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	flag_control(char **cmd, int *j)
{
	int	i;

	i = 0;
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		while (cmd[i] != NULL && ft_strncmp(cmd[i], "-n",
				ft_strlen("-n")) == 0 && cmd[i][*j] == '\0')
		{
			if (cmd[i][*j])
				(*j)++;
		}
		return (1);
	}
	return (0);
}

void	echo(char **cmd)
{
	int	flag;
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (!cmd[0][1])
		return ;
	flag = flag_control(cmd, &j);
	while (cmd[i] && cmd[i][j])
	{
		printf("%s", cmd[i]);
		if (cmd[i] && cmd[i] && cmd[i])
		{
			printf(" ");
			j++;
		}
		if (!cmd[i][j])
			break ;
	}
	if (!flag)
		printf("\n");
	exit(0);
}
