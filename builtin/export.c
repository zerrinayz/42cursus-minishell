/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:47:05 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/13 17:59:02 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_env(t_program *program)
{
	t_list	*list;

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

void	equals(char *cmd, int *k)
{
	while (cmd[*k] != '\0' && cmd[*k] != 61)
		(*k)++;
	if (cmd && cmd[*k] == 61)
		(*k)++;
}
static char	*equals_key(char *cmd)
{
	char	*equ_key;
	int		len;
	int		i;

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

void	export(t_program *program, char **cmd)
{
	int		i;
	int		k;
	int		equal;
	char	*key;
	char	*content;
	t_list	*node;
	t_list	*node2;
	char	*equ_key;

	equal = 0;
	k = 0;
	i = 1;

	if (!cmd[i])
		export_env(program);
	else if (cmd[i])
	{
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
			{
				equals(cmd[i], &k);
				equal = k;
				key = ft_substr(cmd[i], 0, k - 1);
				equals(cmd[i], &k);
				content = ft_substr(cmd[i], equal, k);
				search_set_env(program, key, content);
				if (program->export_flag == 0)
				{
					node = ft_lstnew(content, key);
					node2 = ft_lstnew(content, key);
					ft_lstadd_back(&program->envp_list, node);
					ft_lstadd_back(&program->export_list, node2);
				}
				free(key);
				free(content);
			}
			else
			{
				node = ft_lstnew("(null)", cmd[i]);
				ft_lstadd_back(&program->export_list, node);
			}
			free(equ_key);
			i++;
		}
	}
}
