/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:11:08 by zayaz             #+#    #+#             */
/*   Updated: 2024/09/30 19:46:49 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *min_pipe(char *input)
{
	while (*input && !(*input == '\'' || *input == '\"'))
		input++;
	if (*input)
		input++;
	return (input);
}

static char *pipe_in_ridect(char *input)
{
	while (*input == '<' || *input == '>')
		input++;
	while (*input == 32 && *input != '|')
		input++;
	return (input);
}
int p_pipe(t_program *program, char *input)
{
	(void)program;
	if (*input == '|')
		return (error_message("syntax error to pipe"));
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
			input = min_pipe(input + 1);
		if ((*input == '<' || *input == '>'))
		{
			input = pipe_in_ridect(input);
			if (*input == '|')
				return (error_message("syntax error to pipe"));
		}
		else if (*input == '|')
		{
			input++;
			while (*input == 32)
				input++;
			if (*input == '\0' || *input == '|')
				return (error_message("syntax error to pipe"));
		}
		if (*input != '\0')
			input++;
	}
	return (1);
}
