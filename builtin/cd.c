/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:23:50 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/07 22:30:02 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *search_env(t_program *program, char *key)
{
	t_list *current;
	char *env;

	env = NULL;
	current = program->envp_list;
	while (current->key)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			env = current->content;
			break;
		}
		current = current->next;
	}
	return (env);
}
void search_set_env(t_program *program, char *key, char *content)
{
	t_list *current;

	current = program->envp_list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			program->export_flag = 1;
			current->content = zi_strlcpy(current->content, content,
										  ft_strlen(content));
			return;
		}
		if (!current->next)
			break;
		current = current->next;
	}
	program->export_flag = 0;
}

static void update_env(t_program *program, char *cwd)
{
	char *oldpwd;

	oldpwd = search_env(program, "PWD");
	search_set_env(program, "OLDPWD", oldpwd);
	search_set_env(program, "PWD", cwd);
}

void cd(t_program *program, t_lexer ***parser_input)
{
	char *home;
	char *path;
	char cwd[1024];

	(void)parser_input;
	home = NULL;
	if (parser_input[0][1] == NULL || (ft_strncmp(parser_input[0][1]->cmd, "~",
												  ft_strlen(parser_input[0][1]->cmd)) == 0))
	{
		home = search_env(program, "HOME");
		chdir(home);
		getcwd(cwd, sizeof(cwd));
	}
	else if (ft_strncmp(parser_input[0][1]->cmd, "..",
						ft_strlen(parser_input[0][1]->cmd)) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		chdir("..");
		getcwd(cwd, sizeof(cwd));
	}
	else if (parser_input[0][1])
	{
		path = parser_input[0][1]->cmd;
		if (access(path, F_OK) == 0)
		{
			getcwd(cwd, sizeof(cwd));
			chdir(path);
			getcwd(cwd, sizeof(cwd));
		}
		else
			printf("cd: %s No such file or directory\n", path);
	}
	update_env(program, cwd);
}
