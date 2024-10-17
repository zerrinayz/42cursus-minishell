/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:25 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/16 18:48:20 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_program	*program;
	char		*tmp;

	program = NULL;
	(void)argv;
	if (argc != 1)
		error_message("Unvalid argument");
	program = malloc(sizeof(t_program));
	ft_init_program(program, envp);
	while (1)
	{
		global_signal = 0;
		program->input = readline("minishell 🐥>");
		tmp = ft_strtrim(program->input, " ");
		free(program->input);
		program->input = tmp;
		if (program->input)
		{
			add_history(program->input);
			if (!ft_strncmp(program->input, "exit", 5))
			{
				break ;
			}
		}
		if (program->input == NULL)
		{
			printf("exit\n");
			// exit codelarına bak
			exit(1);
		}
		if (!ft_parser(program, program->input))
			break ;
		if(heredoc_count(program)>0)
			heredoc_run(program);
		zi_exec(program);
		// exec
		free_parser_input(program);
		free(tmp);
	}
	free_program(program);
	// system("leaks minishell");
}
