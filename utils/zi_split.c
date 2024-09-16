/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zi_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:25:37 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/15 19:05:36 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*in_quote_string(char *s, char c)
{
	s++;
	while (*s && (*s != '\'' && *s != '\"'))
		s++;
	while (*s && *s != c)
		s++;
	return (s);
}

 int	count_string(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			s = in_quote_string(s, c);
		else
		{
			while (*s && *s != c && (*s != '\'' && *s != '\"'))
				s++;
		}
		if (*s == c || *s == '\0' || *s + 1 == '\0')
		{
			count++;
			if (*s)
				s++;
		}
	}
	return (count);
}

static int	in_quote_char(char *s, char c, int i)
{
	i++;
	while (s[i] && (s[i] != '\'' && s[i] != '\"'))
		i++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = in_quote_char(s, c, i);
			if (s[i] == c || s[i] == '\0')
				return (i);
		}
		else
		{
			while (s[i] && s[i] != c && (s[i] != '\'' && s[i] != '\"'))
				i++;
			if (s[i] == c || s[i] == '\0' || s + i + 1 == NULL)
			{
				if (s[i] == c || s[i] == '\0')
					return (i);
			}
		}
	}
	return (i);
}



char	**zi_split(t_program *program, char *s, char c)
{
	int		word;
	int		i;
	int		x;
	char	**s1;

	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	word = count_string(s, c);
	s1 = ft_calloc(word + 1, sizeof(char *));
	if (!s1)
		return (NULL);
	while (*s)
	{
		i = count_char(s, c);
		s1[x++] = ft_substr(s, 0, i);
		s = walk_string(program, s, c);
	}
	s1[x] = NULL;
	return (s1);
}
