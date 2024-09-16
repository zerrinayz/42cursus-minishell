/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:21:01 by zayaz             #+#    #+#             */
/*   Updated: 2024/09/14 17:27:05 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_string(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			return (count);
		while (s[i] != c && s[i])
			i++;
		count++;
	}
	return (count);
}

static int	count_char(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		x;
	int		word;
	char	**s1;

	x = 0;
	if (!s)
		return (NULL);
	word = count_string(s, c);
	s1 = ft_calloc(word + 1, sizeof(char *));
	if (!s1)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		i = count_char(s, c);
		s1[x++] = ft_substr(s, 0, i);
		while (*s && *s != c)
			s++;
	}
	s1[x] = NULL;
	return (s1);
}
