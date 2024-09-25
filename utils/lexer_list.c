/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:25:38 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/24 17:12:01 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	zi_striteri(t_lexer *s, void f(t_lexer *))
{
	if (!s || !f)
		return ;
	f(s);
}

int	zi_strrchr(const char *s, int c, int i)
{
	if (!s[i])
		return (0);
	while (i >= 0 && s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (1);
		i--;
	}
	return (0);
}
char	*zi_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	dst = (char *)malloc(dstsize * sizeof(char) + 1);
	i = 0;
	if (!src || !dstsize)
		return (dst);
	while (i <= (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	zi_strlen(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}