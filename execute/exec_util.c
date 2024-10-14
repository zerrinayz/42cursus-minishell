/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:40:25 by zayaz             #+#    #+#             */
/*   Updated: 2024/10/13 18:25:37 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_c(t_program *program, int *i)
{
	int	j;

	j = 0;
	while (program->parser_input[*i] && program->parser_input[*i][j])
	{
		if (program->parser_input[*i][j]->key == 7)
			return (1);
		if (program->parser_input[*i][j]->key)
			j++;
	}
	return (0);
}
int	pipe_count(t_program *program)
{
	int	i;

	i = 0;
	while (program->parser_input[i] != NULL)
		i++;
	return (i);
}

char	*zi_sec_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	q_type;
	int		j;

	dst = (char *)malloc(dstsize * sizeof(char) + 1);
	i = 0;
	j = 0;
	if (!src || !dstsize)
		return (dst);
	while (src[i] && i <= (dstsize - 1))
	{
		if (src[i] == '\'' || src[i] == '\"')
			q_type = src[i];
		i++;
		while (src[i] && q_type != src[i])
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		if (q_type == src[i])
		{
			i++;
			while (src[i] && (src[i] != '\'' && src[i] != '\"'))
			{
				dst[j] = src[i];
				i++;
				j++;
			}
		}
	}
	dst[j] = '\0';
	return (dst);
}