/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:47:05 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/14 17:46:56 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void export_env(t_program *program)
{
	t_list *list;

	list = program->export_list;
	while (list != NULL)
	{
		if (list && (list->content != NULL && list->key != NULL))
		{
			if ((ft_strncmp(list->content, "(null)",
							ft_strlen(list->content))) != 0)
				printf("declare -x %s=%s\n", (char *)list->key,
					   (char *)list->content);
			else if (ft_strncmp(list->content, "(null)",
								ft_strlen(list->content)) == 0)
				printf("declare -x %s\n", (char *)list->key);
		}
		list = list->next;
	}
}

static void equals(char *cmd, int *k)
{
	while (cmd[*k] != '\0' && cmd[*k] != 61)
		(*k)++;
	if (cmd && cmd[*k] == 61)
		(*k)++;
}
static char *equals_key(char *cmd)
{
	char *equ_key;
	int len;
	int i;

	equ_key = NULL;
	len = ft_strlen(cmd);
	equ_key = malloc(len + 1);
	if (equ_key == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (cmd[i] == 61)
		{
			equ_key[i] = '\0';
			return (equ_key);
		}
		equ_key[i] = cmd[i];
		i++;
	}
	equ_key[i] = '\0';
	return (equ_key);
}

static void export_run(t_program *program, char *cmd, int i)
{
	char *equ_key;
	t_list *node;

	while (cmd[i])
	{
		equ_key = equals_key(cmd[i]);
		if (!check_identifier(equ_key))
		{
			printf("export: `%s':not a valid identifier\n",
				   cmd[i]);
			free(equ_key);
		}
		else if (ft_strchr(cmd[i], 61) != 0)
			equal_in_export(program, cmd, &i);
		else
		{
			node = ft_lstnew("(null)", cmd[i]);
			ft_lstadd_back(&program->export_list, node);
		}
		free(equ_key);
		i++;
	}
}

void export(t_program *program, char **cmd)
{
	int i;

	i = 1;

	if (!cmd[i])
		export_env(program);
	else if (cmd[i])
		export_run(program, cmd, i);
}
