/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:25:00 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/01 19:25:03 by zayaz            ###   ########.fr       */
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
static int	zi_strchr(const char *s, int c, char type)
{
	while (*s && *s != (char)c && *s != type)
		s++;
	if (*s == (char)c)
		return (1);
	return (0);
}
size_t	zi_strlen(const char *s, char c, int dhand)
{
	size_t	i;
	char	q_type;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && dhand)
		{
			q_type = s[i];
			if (q_type == '\"')
			{
				if (zi_strchr(s + i + 1, 36, q_type) != 0)
					return (i);
			}
			i++;
			while (s[i] && s[i] != q_type)
				i++;
		}
		if (s[i] == c)
			return (i);
		if (s[i])
			i++;
	}
	return (i);
}
