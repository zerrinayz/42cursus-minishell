#include "../minishell.h"

//  echo "$HOME"'$HOME''"$HOME"' birden fazla dolarlı ise dolar olarak ----dolar
// setle . tırnak temizlerken birden fazla varsa içini tek tek temizle(execde)

//"$HOME"

int	is_env(char *parser_input, char quote_type)
{
	(void)quote_type;
	if (ft_strchr(parser_input, 36))
		return (0);
	return (1);
}

char	*get_env(t_program *program, char *parser_input, char c)
{
	while (program->envp_list)
	{
		if (!ft_strncmp(program->envp_list->key, parser_input,
				zi_strlen(parser_input, c)))
		{
			return (zi_strlcpy(parser_input, program->envp_list->content,
					ft_strlen(program->envp_list->content)));
		}
		program->envp_list = program->envp_list->next;
	}
	return (NULL);
}

void	loc_dolar(t_program *program, t_lexer *parser_inputiz)
{
	char	*parser_input;
	char	*tmp;
	int		i;
	int		j;

	char	quote_type;
	char	*tmp2;
	char	*tmp3;
	quote_type = '\0';
	tmp = NULL;
	j = 0;
	tmp = malloc(sizeof(char) * (zi_strlen(parser_inputiz->cmd, '$') + 1));
	if(!tmp)
		tmp=NULL;                 
	parser_input = parser_inputiz->cmd;
	i = 0;
	while (parser_input[i])
	{
		if (parser_input[i] == '\'' || parser_input[i] == '\"'){
			quote_type = parser_input[i];
		}
		 if ( parser_input[i] != '$' && parser_input[i])
		{
			tmp[j] = parser_input[i];
			i++;
			j++;
		}
		if (parser_input[i] == '$')
		{
			i++;
			tmp2 = get_env(program, &parser_input[i], quote_type);
			if (tmp2)
			{
				while (parser_input[i] && parser_input[i] != '\''
					&& parser_input[i] != '\"')
					i++;
				tmp3 = ft_strchr(parser_input + i, quote_type);
				break;
			}else if(!tmp2)
				break;
		}
	}
	tmp[j] = '\0';
	tmp = ft_strjoin(tmp, tmp2);
	parser_inputiz->cmd = ft_strjoin(tmp, tmp3);
	free(tmp);
}

int	count_dolar(char *parser_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (parser_input[i])
	{
		if (parser_input[i] == '$')
			count++;
		i++;
	}
	return (count);
}
