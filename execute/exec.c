/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:45:46 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/14 16:56:09 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_command(t_program *program)
{
	(void)program;
	// exec
}

void exec_builtin(t_program *program)
{
	// if ((ft_strncmp(program->cmd[0], "exit",
	//	ft_strlen(program->cmd[0])) == 0))
	// 	echo(program->cmd);
	if ((ft_strncmp(program->cmd[0], "echo", ft_strlen(program->cmd[0])) == 0))
		echo(program->cmd);
	else if ((ft_strncmp(program->cmd[0], "pwd",
						 ft_strlen(program->cmd[0])) == 0))
		pwd();
	else if ((ft_strncmp(program->cmd[0], "cd",
						 ft_strlen(program->cmd[0])) == 0))
		cd(program, program->cmd);
	else if ((ft_strncmp(program->cmd[0], "unset",
						 ft_strlen(program->cmd[0])) == 0))
		zi_unset(program, program->cmd);
	else if ((ft_strncmp(program->cmd[0], "export",
						 ft_strlen(program->cmd[0]) == 0)))
		export(program, program->cmd);
	else if ((ft_strncmp(program->cmd[0], "env",
						 ft_strlen(program->cmd[0])) == 0))
		env(program, program->cmd);
}
void create_fork(t_program *program, int *i)
{
	pid_t pid_fork;

	pid_fork = fork();
	// exit atman gerek burada
	if (pid_fork == -1)
		return;
	if (pid_fork == 0)
	{
		if (program->hd_count > 0)
		{
			printf("count: %d\n",program->hd_count);
			
			heredoc_run(program);
		}
		if (redirect_c(program, i))
		{
			printf("geldim rido\n");
			redirect(program, i);
		}
		// echo a >as< biy
		// program->cmd;
		// redirect tırnağını temizlemeyi unutmayın
		// exec_builtin(program);
		//exec_command(program);
		//printf("çıktım");
		exit(0);
	}
}
void zi_exec(t_program *program)
{
	int i;

	i = 0;
	// process pipe için
	// fork komut sayısı kadar
	program->p_count = pipe_count(program);
	program->hd_count = heredoc_count(program);
	if (program->p_count > 0)
	{
		program->process = malloc(sizeof(t_process) * (program->p_count + 1));
		while (i < program->p_count)
			pipe(program->process[i++].fd);
	}
	i = 0;
	while (i < program->p_count + 1)
	{
		create_fork(program, &i);
		i++;
	}
	i = 0;
	while (program->p_count > 0 && i < program->p_count)
		waitpid(program->process[i++].pid, NULL, 0);
	// close_pipe;
}
