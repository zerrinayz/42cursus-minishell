/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:25 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/15 20:36:58 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_envp_list(t_list *envp_list)
// {
// 	t_list	*temp;

// 	while (envp_list)
// 	{
// 		temp = envp_list->next;
// 		free(envp_list->content);
// 		free(envp_list->key); // Eğer içerik dinamik olarak tahsis edildiyse
// 		// Eğer içerik dinamik olarak tahsis edildiyse
// 		free(envp_list); // Liste düğümünü serbest bırak
// 		envp_list = temp;
// 	}
// }

// void	free_program(t_program *program)
// {
// 	if (!program)
// 		return ;
// 	if (program->input)
// 		free(program->input);
// 	if (program->envp_list)
// 		free_envp_list(program->envp_list);
// 	free(program);
// }
int	main(int argc, char **argv, char **envp)
{
	t_program	*program;

	program = NULL;
	(void)argv;
	if (argc != 1)
		error_message("Unvalid argument");
	program = malloc(sizeof(t_program));
	ft_init_program(program, envp);
	while (1)
	{
		program->input = readline("minishell 🐥>");
		program->input = ft_strtrim(program->input, " ");
		if (program->input)
		{
			add_history(program->input);
			if (!ft_strncmp(program->input, "exit", 5))
				exit(0);
		}
		if (program->input == NULL)
		{
			printf("exit\n");
			// exit codelarına bak
			exit(1);
		}
		if (!ft_parser(program, program->input))
			break ;
	}
}

// void __attribute__((constructor)) a()
// {
// 	system("leaks minishell");
// 