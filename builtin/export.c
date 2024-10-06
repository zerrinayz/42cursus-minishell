/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:47:05 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/05 18:11:07 by itulgar          ###   ########.fr       */
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

void	equals(char *parser_input, int *k)
{
	while (parser_input[*k] != '\0' && parser_input[*k] != 61)
		(*k)++;
	if (parser_input && parser_input[*k] == 61)
		(*k)++;
}
void	export(t_program *program, t_lexer ***parser_input)
{
	int		i;
	int		k;
	int		equal;
	char	*key;
	char	*content;
	t_list	*node;
	t_list	*node2;

	equal = 0;
	k = 0;
	i = 1;
	if (parser_input[0] == NULL)
		return ;
	if (parser_input[0][i] == NULL)
		export_env(program);
	else if (parser_input[0][i]->cmd)
	{
		while (parser_input[0][i])
		{
			if (!check_identifier(parser_input[0][i]->cmd)){
				printf("unset: `%s':not a valid identifier\n",
					parser_input[0][i]->cmd);
			}
			else if (ft_strchr(parser_input[0][i]->cmd, 61) != 0)
			{
				equals(parser_input[0][i]->cmd, &k);
				equal = k;
				key = ft_substr(parser_input[0][i]->cmd, 0, k - 1);
				equals(parser_input[0][i]->cmd, &k);
				content = ft_substr(parser_input[0][i]->cmd, equal, k);
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
				node = ft_lstnew("(null)", parser_input[0][i]->cmd);
				ft_lstadd_back(&program->export_list, node);
			}
			i++;
		}
	}
}
