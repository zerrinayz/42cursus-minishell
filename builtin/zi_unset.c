/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:38:58 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/05 18:23:52 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	del(void *content, void *key)
{
	free(content);
	free(key);
}

static t_list	*zi_lstdelone(t_list **lst, t_list *node, void (*del)(void *,
			void *))
{
	t_list	*tmp;

	if (!lst)
		return (*lst);
	if (*lst == node)
	{
		tmp = (*lst)->next;
		del((*lst)->content, (*lst)->key);
		free(*lst);
		*lst = tmp;
		return (*lst);
	}
	tmp = *lst;
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	if (tmp && tmp->next == node)
	{
		tmp->next = node->next;
		del(node->content, node->key);
		free(node);
	}
	return (*lst);
}

static void	search_del_env(t_program *program, char *key, t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			program->unset_flag = 1;
			*lst = zi_lstdelone(lst, current, del);
			break ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	program->unset_flag = 0;
}

 int	check_identifier(char *parser_input)
{
	int	i;

	i = 0;
	if (ft_isalpha(parser_input[i]) || parser_input[i] == 95)
	{
		while (parser_input[i])
		{
			if ((parser_input[i] >= 32 && parser_input[i] <= 47)
				|| (parser_input[i] >= 58 && parser_input[i] <= 64)
				|| (parser_input[i] >= 91 && parser_input[i] <= 96
					&& parser_input[i] != 95) || (parser_input[i] >= 123
					&& parser_input[i] <= 126))
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	zi_unset(t_program *program, t_lexer ***parser_input)
{
	int i = 1;
	if (parser_input[0] == NULL || parser_input[0][1] == NULL)
		return ;
	if (parser_input[0][i]->cmd)
	{
		while (parser_input[0][i])
		{
			if (!check_identifier(parser_input[0][i]->cmd))
				printf("unset: `%s':not a valid identifier\n",
					parser_input[0][i]->cmd);
			else
			{
				search_del_env(program, parser_input[0][i]->cmd,
					&program->envp_list);
				search_del_env(program, parser_input[0][i]->cmd,
					&program->export_list);
			}
			i++;
		}
	}
}
