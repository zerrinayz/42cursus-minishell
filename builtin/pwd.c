/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:37:45 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/13 13:59:23 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	// büyük küçük harf duyarsız
	char pwd[1024];
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	exit(0);
}