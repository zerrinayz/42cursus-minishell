/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:42:00 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/15 20:15:45 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *str)
{
	printf("<< Error: %s honey >>\n", str);
	//system("leaks minishell");
	printf("biy\n");
	//exit(1);
	return (0);
}