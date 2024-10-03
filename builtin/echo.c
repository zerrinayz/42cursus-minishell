/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:36:01 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/02 15:47:03 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	flag_control(t_lexer ***flag_input, int *j)
{
	int	i;

	i = 0;
	if (flag_input[0][1]->cmd[0] == '-' && flag_input[0][1]->cmd[1] == 'n'
		&& flag_input[i][1]->cmd[2] == '\0')
	{
		while (ft_strncmp(flag_input[i][*j]->cmd, "-n", ft_strlen("-n")) == 0
			&& flag_input[i][*j]->cmd[2] == '\0')
		{
			printf("geldim\n");
			if (flag_input[i][*j]->cmd)
				(*j)++;
		}
		return (1);
	}
	return (0);
}

void	echo(t_lexer ***parser_input)
{
	int	flag;
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (!parser_input[0])
		return ;
	flag = flag_control(parser_input, &j);
	while (parser_input[i] && parser_input[i][j] && parser_input[i][j]->cmd)
	{
		printf("%s", parser_input[i][j]->cmd);
		if (parser_input[i] && parser_input[i][j] && parser_input[i][j]->cmd)
		{
			printf(" ");
			j++;
		}
		if (!parser_input[i][j])
			break ;
	}
	if (!flag)
		printf("\n");
	exit(1);
}
