/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:19:08 by zayaz             #+#    #+#             */
/*   Updated: 2024/09/14 16:30:37 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_quote(char *input)
{
	while (*input && !(*input == '\'' || *input == '\"'))
		input++;
	if (*input)
		input++;
	return (input);
}

static int	count_redirect(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (0);
	while (*input && (*input == '<' || *input == '>'))
	{
		input++;
		i++;
	}
	if (i > 2)
		return (0);
	return (1);
}

int	p_redirection(char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
			input = skip_quote(input + 1);
		if (!count_redirect(input))
			return (error_message("syntax error to redirection"));
		if ((*input == '<' || *input == '>'))
		{
			while (*input == '<' || *input == '>')
				input++;
			while (*input == 32)
				input++;
			if (*input == '\0' || (*(input) == '<' || *(input) == '>'))
				return (error_message("syntax error to redirection"));
		}
		if (*input != '\0')
			input++;
	}
	return (1);
}
