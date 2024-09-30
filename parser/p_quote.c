/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:10:17 by zayaz             #+#    #+#             */
/*   Updated: 2024/09/30 19:47:09 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *quote_check(t_program *program, char *input, char c)
{
	int i;

	i = 0;
	program->check_quote = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			program->check_quote = 1;
			break;
		}
		i++;
	}
	return (input + i);
}

static char *quote_handler(t_program *program, char *input, char quote)
{
	input = quote_check(program, input + 1, quote);
	return (input);
}

int p_quote(t_program *program, char *input)
{
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
			input = quote_handler(program, input, *input);
		if (!program->check_quote)
			return (error_message("syntax error to quote"));
		if (!*input)
			break;
		input++;
	}
	return (1);
}
