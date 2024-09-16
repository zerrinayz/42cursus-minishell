/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:57:38 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/15 20:22:09 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int clean_input(t_program *program, char *input)
{
	char **pipe_input;
	char **split_space;
	int i;
	int k;
	int j;
	int z;
	i = 0;
	z = 0;
	k = 0;
	j = 0;
	pipe_input = zi_split(program, input, '|');
	program->parser_input = (char ***)malloc((count_string(input, '|') + 1) * sizeof(char **));
	if (!program->parser_input)
		return error_message("Memory allocation");
	while (pipe_input[i])
	{
		split_space = zi_split(program, pipe_input[i], ' ');

		program->parser_input[k] = (char **)malloc((count_string(pipe_input[i], ' ') + 1) * sizeof(char *));
		if (!program->parser_input[k])
			return error_message("Memory allocation");
		j = 0;
		z = 0;
		while (split_space[j])
		{
			if (split_space[j][0] != '\0' && split_space[j][0] != ' ')
			{
				program->parser_input[k][z] = split_space[j];
				printf("Command %d, Arg %d: %s\n", k, z, program->parser_input[k][z]);
				z++;
			}
			j++;
		}
		program->parser_input[k][z] = NULL;
		k++;
		i++;
	}
	program->parser_input[k] = NULL;
	i = 0;
	while (split_space[i])
	{
		free(split_space[i]);
		i++;
	}
	free(split_space);
	free(pipe_input);
	return 1;
}

int ft_parser(t_program *program, char *input)
{
	if (!p_quote(program, input))
		return (0);
	if (!p_redirection(program->input))
		return (0);
	if (!p_pipe(input))
		return (0);
	if (!clean_input(program, input))
		return (0);

	return (1);
}
