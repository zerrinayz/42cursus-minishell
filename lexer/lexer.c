/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:42:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/03 19:16:28 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *pass_quote_cmd(t_lexer *parser_input, char *tmp, int *j, int *i)
{
	char q_type;

	if (parser_input->cmd[*i] == '\'' || parser_input->cmd[*i] == '\"')
	{
		q_type = parser_input->cmd[*i];
		(*i)++;
		while (parser_input->cmd[*i] && parser_input->cmd[*i] != q_type)
		{
			tmp[*j] = parser_input->cmd[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (parser_input->cmd[*i] && parser_input->cmd[*i] != '\"' && parser_input->cmd[*i] != '\'')
	{
		tmp[*j] = parser_input->cmd[*i];
		(*j)++;
	}
	return (tmp);
}
void f(t_lexer *parser_inputiz)
{
	int i;
	char *tmp;
	int j;

	tmp = (char *)malloc((ft_strlen(parser_inputiz->cmd) + 1) * sizeof(char));
	if (!tmp)
		printf("Bellek ayırma hatası!\n");
	else
	{
		j = 0;
		i = 0;
		while (parser_inputiz->cmd[i] != '\0')
		{
			tmp = pass_quote_cmd(parser_inputiz, tmp, &j, &i);
			if (parser_inputiz->cmd[i])
				i++;
		}
		tmp[j] = '\0';
		parser_inputiz->cmd = zi_strlcpy(parser_inputiz->cmd, tmp,
										 ft_strlen(parser_inputiz->cmd));
	}
	free(tmp);
}

void quote_clean(t_program *program)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (program->parser_input[i])
	{
		j = 0;
		while (program->parser_input[i][j])
		{
			if (ft_strchr(program->parser_input[i][j]->cmd, 36))
				dolar_handler(program, program->parser_input[i][j]);
			zi_striteri(program->parser_input[i][j], f);
			printf("cmd:%d: arg:%d:%s  key:%d\n", i, j,
				   program->parser_input[i][j]->cmd,
				   program->parser_input[i][j]->key);
			j++;
		}
		i++;
	}
	// echo(program->parser_input);
	// pwd();
	// cd(program,program->parser_input);
	// exit(1);
	//env(program, program->parser_input);
	export(program, program->parser_input);
}
