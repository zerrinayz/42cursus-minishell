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

// void clean_input(t_program *program, char *input)
// {
//     char **pipe_input;
//     char **split_command;
//     int i, j, k;

//     if (!input || input[0] == '\0')
//     {
//         printf("Input is empty or NULL\n");
//         return;
//     }

//     pipe_input = zi_split(program, input, '|');
//     if (!pipe_input)
//     {
//         printf("Error in zi_split for pipe_input\n");
//         return;
//     }

//     program->parser_input = (char ***)malloc((count_string(input, '|') + 1) * sizeof(char **));
//     if (!program->parser_input)
//     {
//         printf("Memory allocation failed for parser_input\n");
//         return;
//     }

//     i = 0;
//     k = 0;
//     while (pipe_input[i])
//     {
//         split_command = zi_split(program, pipe_input[i], ' ');
//         if (!split_command)
//         {
//             printf("Error in zi_split for split_command\n");
//             i++;
//             continue;
//         }

//         int has_valid_arg = 0;
//         j = 0;
//         while (split_command[j] != NULL) // 'for' yerine 'while' kullanıyoruz
//         {
//             if (split_command[j][0] != '\0')
//             {
//                 if (!has_valid_arg)
//                 {
//                     program->parser_input[k] = (char **)malloc((count_string(pipe_input[i], ' ') + 1) * sizeof(char *));
//                     if (!program->parser_input[k])
//                     {
//                         printf("Memory allocation failed for parser_input[k]\n");
//                         return;
//                     }
//                     has_valid_arg = 1;
//                 }
//                 program->parser_input[k][j] = ft_strdup(split_command[j]);
//                 if (!program->parser_input[k][j])
//                 {
//                     printf("Error duplicating string\n");
//                     return;
//                 }
//                 printf("Command %d, Arg %d: %s\n", k, j, program->parser_input[k][j]);
//             }
//             j++;  // 'for' içindeki artış kısmı
//         }

//         if (has_valid_arg)
//         {
//             program->parser_input[k][j] = NULL;
//             k++;
//         }

//         i++;  // 'for' içindeki artış kısmı
//     }

//     program->parser_input[k] = NULL;
// }

//"a" | b | c "ab "
// "a" |
// b |
// c "ab "

static int clean_input(t_program *program, char *input)
{
	char **pipe_input;
	char **split_space;
	int i;
	i = 0;
	pipe_input = zi_split(program, input, '|');
	program->parser_input = (char ***)malloc((count_string(input, '|') + 1) * sizeof(char **));
	if (!program->parser_input)
		return error_message("Memory allocation");
	while (pipe_input[i])
	{
		split_space = zi_split(program, pipe_input[i], 32);
		printf("dizi %s", split_space[i]);
		i++;



	}
	return 1;
}

int ft_parser(t_program *program, char *input)
{
	if (!p_quote(program, input))
		return (0);
	printf("geldim\n");
	if (!p_redirection(program->input))
		return (0);
	if (!p_pipe(input))
		return (0);
	if (!clean_input(program, input))
		return (0);

	return (1);
}
