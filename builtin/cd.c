/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:23:50 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/14 17:26:32 by zerrinayaz       ###   ########.fr       */
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
	printf("cwd: %s \n", cwd);
}

static void cd_path(char *cwd, char *cmd)
{
	char *path;

	path = cmd[1];
	if (access(path, F_OK) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		chdir(path);
		getcwd(cwd, sizeof(cwd));
	}
	else
		printf("cd: %s No such file or directory\n", path);
}

void cd(t_program *program, char **cmd)
{
	char *home;
	char cwd[1024];

	if (cmd[1] == NULL || (ft_strncmp(cmd[1], "~", ft_strlen(cmd[1])) == 0))
	{
		home = search_env(program, "HOME");
		chdir(home);
		getcwd(cwd, sizeof(cwd));
	}
	else if (ft_strncmp(cmd[1], "..", ft_strlen(cmd[1])) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		chdir("..");
		getcwd(cwd, sizeof(cwd));
	}
	else if (cmd[1])
		cd_path(cwd, cmd[1]);
	update_env(program, cwd);
}
