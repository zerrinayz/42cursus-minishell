/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:42:31 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/05 19:17:01 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pass_quote_cmd(t_lexer *parser_input, char *tmp, int *j, int *i)
{
	char	q_type;

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
	else if (parser_input->cmd[*i] && parser_input->cmd[*i] != '\"'
		&& parser_input->cmd[*i] != '\'')
	{
		tmp[*j] = parser_input->cmd[*i];
		(*j)++;
	}
	return (tmp);
}
void	f(t_lexer *parser_inputiz)
{
	int		i;
	char	*tmp;
	int		j;

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

void	quote_clean(t_program *program)
{
	int	i;
	int	j;

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
			// printf("cmd:%d: arg:%d:%s  key:%d\n", i, j,
			// 	program->parser_input[i][j]->cmd,
			// 	program->parser_input[i][j]->key);
			j++;
		}
		i++;
	}
	if (!program->parser_input[0])
		return ;
	if ((ft_strncmp(program->parser_input[0][0]->cmd, "exit",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		echo(program->parser_input);
	else if ((ft_strncmp(program->parser_input[0][0]->cmd, "echo",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		echo(program->parser_input);
	else if ((ft_strncmp(program->parser_input[0][0]->cmd, "pwd",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		pwd();
	else if ((ft_strncmp(program->parser_input[0][0]->cmd, "cd",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		cd(program, program->parser_input);
	else if ((ft_strncmp(program->parser_input[0][0]->cmd, "unset",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		zi_unset(program, program->parser_input);
	else if ((ft_strncmp(program->parser_input[0][0]->cmd, "export",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		export(program, program->parser_input);
	else if ((ft_strncmp(program->parser_input[0][0]->cmd, "env",
				ft_strlen(program->parser_input[0][0]->cmd)) == 0))
		env(program, program->parser_input);
}

// 0 1
//0
//dup2() ->1 