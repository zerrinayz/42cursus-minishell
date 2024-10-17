/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:20:33 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/16 19:27:10 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_count(t_program *program)
{
	int	i;
	int	j;
	int	hd;

	i = 0;
	j = 0;
	hd = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (zi_redirectchr(program->parser_input[i][j]->cmd, '<') != 0
				&& program->parser_input[i][j]->key == 7)
				hd++;
			j++;
		}
		i++;
	}
	return (hd);
}

int	zi_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
static void	parent_heredoc(t_process hd_process)
{
	global_signal = IN_PARENT;
	close(hd_process.fd[1]);
}
void	heredoc(char *s)
{
	pid_t		pid_fork;
	char		*line;
	t_process	hd_process;

	if (pipe(hd_process.fd) == -1)
	{
		perror("pipe creation failed");
		exit(1);
	}
	close(hd_process.fd[0]);
	pid_fork = fork();
	if (pid_fork == -1)
		return ;
	if (pid_fork == 0)
	{
		global_signal = IN_HERADOC;
		while (1)
		{
			line = readline(">");
			ft_putstr_fd(line, hd_process.fd[1]);
			ft_putchar_fd("\n", hd_process.fd[1]);
			if (!line)
				break ;
			if (zi_strcmp(s, line) == 0)
			{
				free(line);
				break ;
			}
			free(line);
		}
		close(hd_process.fd[1]);
		exit(0);
	}
	else
		parent_heredoc(hd_process);
}

void	heredoc_run(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (zi_redirectchr(program->parser_input[i][j]->cmd, '<') != 0
				&& program->parser_input[i][j]->key == 7)
				go_redirect(program, heredoc, '<', &i, &j, 1);
			j++;
		}
		i++;
	}
}
