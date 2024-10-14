/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:53:16 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/14 16:48:20 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int zi_redirectchr(const char *s, char c)
{
	char type;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			type = *s;
			s++;
			while (*s && *s != type)
				s++;
			s++;
		}
		if (*s == c && *(s + 1) == c)
			return (1);
		if (*s)
			s++;
	}
	return (0);
}

static void run_output(char *s)
{
	int fd;

	fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return;
	}
	close(fd);
}

static void run_input(char *s)
{
	int fd;

	fd = open(s, O_RDWR);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directoryss\n", s);
		return;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return;
	}
	close(fd);
}

static void append_output(char *s)
{
	int fd;

	fd = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error opening file");
		close(fd);
		return;
	}
	close(fd);
}

void go_redirect(t_program *program, void run_redirect(char *), char key,
				 int *i, int *j, int split_rd)
{
	int k;
	char **redi_cmd;
	char *dst;
	dst = NULL;
	if (ft_strlen(program->parser_input[*i][*j]->cmd) > 1)
	{
		redi_cmd = zi_split(program, program->parser_input[*i][*j]->cmd, key,
							split_rd);
		k = 1;
		while (redi_cmd[k])
		{
			if (ft_strchr(redi_cmd[k], 34) || ft_strchr(redi_cmd[k], 39))
				redi_cmd[k] = zi_sec_strlcpy(dst, redi_cmd[k],
											 ft_strlen(redi_cmd[k]));
			run_redirect(redi_cmd[k]);
			k++;
		}
	}
	else
		run_redirect(program->parser_input[*i][*j + 1]->cmd);
}

void redirect(t_program *program, int *i)
{
	int j;

	j = 0;
	// echo a > as
	while (program->parser_input[*i][j] != NULL && program->parser_input[*i][j]->cmd)
	{
		if (zi_redirectchr(program->parser_input[*i][j]->cmd, '>') && program->parser_input[*i][j]->key == 7)
			go_redirect(program, append_output, '>', i, &j, 1);
		else if (zi_redirectchr(program->parser_input[*i][j]->cmd, '<') != 1 && ft_strchr(program->parser_input[*i][j]->cmd, '<') != 0 && program->parser_input[*i][j]->key == 7)
			go_redirect(program, run_input, '<', i, &j, 0);
		else if (ft_strchr(program->parser_input[*i][j]->cmd, '>') != 0 && program->parser_input[*i][j]->key == 7)
			go_redirect(program, run_output, '>', i, &j, 0);
		j++;
	}
}
