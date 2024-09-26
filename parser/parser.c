/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:57:38 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/25 18:57:29 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_pipe_input(t_program *program, char *pipe_input, int k)
{
	char	**split_space;
	int		j;
	int		z;

	split_space = zi_split(program, pipe_input, ' ');
	program->parser_input[k] = (t_lexer **)malloc((count_string(pipe_input, ' ')
				+ 1) * sizeof(char *));
	if (!program->parser_input[k])
	{
		free_array(split_space);
		free(pipe_input);
		return (error_message("Memory allocation"), -1);
	}
	j = 0; 
	z = 0;
	while (split_space[j])
	{
		program->parser_input[k][z] = (t_lexer *)malloc(sizeof(t_lexer));
		if (split_space[j][0] != '\0' && split_space[j][0] != ' ')
		{
			program->parser_input[k][z]->cmd = ft_strdup(split_space[j]);
			program->parser_input[k][z]->key = set_meta(program,
					split_space[j]);
			// printf("sos Command %d, Arg %d: %s  key:%d\n", k, z,
			// 	program->parser_input[k][z]->cmd,
			// 	program->parser_input[k][z]->key);
			z++;
		}
		j++;
	}
	free_array(split_space);
	return (z);
}

static int	clean_input(t_program *program, char *input)
{
	char	**pipe_input;
	int		i;
	int		k;
	int		z;

	i = 0;
	z = 0;
	k = 0;
	pipe_input = zi_split(program, input, '|');

	program->parser_input = (t_lexer ***)malloc((count_string(input, '|') + 1)
			* sizeof(char **));
	
	if (!program->parser_input)
	{
		free_array(pipe_input);
		return (error_message("Memory allocation"));
	}
	while (pipe_input[i])
	{
		if ((z = fill_pipe_input(program, pipe_input[i], k)) == -1)
			return (0);
		program->parser_input[k][z] = NULL;
		k++;
		i++;
	}
	program->parser_input[k] = NULL;
	free_array(pipe_input);
	return (1);
}

int	ft_parser(t_program *program, char *input)
{
	if (!p_quote(program, input))
		return (0);
	if (!p_redirection(program, program->input))
		return (0);
	if (!p_pipe(program, input))
		return (0);
	if (!clean_input(program, input))
		return (0);
	quote_clean(program);
	return (1);
}
