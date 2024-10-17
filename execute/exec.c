/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:45:46 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/16 19:41:50 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_command(t_program *program)
{
	(void)program;
	// exec
}

void	exec_builtin(t_program *program)
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
void	create_fork(t_program *program, int *i)
{
	pid_t	pid_fork;

	pid_fork = 0;
	pid_fork = fork();
	if (pid_fork == -1)
		return ;
	if (pid_fork == 0)
	{
		if (redirect_c(program, i))
			redirect(program, i);
		// program->cmd;
		// redirect tırnağını temizlemeyi unutmayın
		// exec_builtin(program);
		// exec_command(program);
		exit(0);
	}
}
void	zi_exec(t_program *program)
{
	int	i;

	i = 0;
	// process pipe için
	// fork komut sayısı kadar
	program->p_count = pipe_count(program);
	i = 0;
	while (i < program->p_count + 1)
	{
		if (program->p_count > 0)
		{
			program->process = malloc(sizeof(t_process) * (program->p_count
						+ 1));
			pipe(program->process[i].fd);
		}
		create_fork(program, &i);
		i++;
	}
	i = 0;
	 while (program->p_count > 0 && i < program->p_count)
	 	waitpid(program->process[i++].pid, NULL, 0);
	// close_pipe;
}
