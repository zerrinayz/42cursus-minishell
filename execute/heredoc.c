/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:20:33 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/14 17:09:35 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int heredoc_count(t_program *program)
{
	int i;
	int j;

	i = 0;
	j = 0;
	program->hd_count = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (zi_redirectchr(program->parser_input[i][j]->cmd, '<') != 0 && program->parser_input[i][j]->key == 7)
				program->hd_count++;
			j++;
		}
		i++;
	}
	return (program->hd_count);
}

int zi_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;

	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
void heredoc(char *s)
{
	char *line;
	printf(" hero %s:\n", s);

	global_signal = IN_HERADOC;
	while (1)
	{
		line = readline(">");
		if (!line)
			break;
		if (zi_strcmp(s, line) == 0)
		{

			printf("geldim hero\n");
			free(line);
			break;
		}
		free(line);
	}
}

void heredoc_run(t_program *program)
{
	int i;
	int j;
	//<<a<< a
	i = 0;
	j = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (zi_redirectchr(program->parser_input[i][j]->cmd, '<') != 0 && program->parser_input[i][j]->key == 7)
			{
				go_redirect(program, heredoc, '<', &i, &j, 1);
				program->hd_count -= 1;
			}
			j++;
		}
		i++;
	}
}
