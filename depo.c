// // // // static int in_quote_space(char *s)
// // // // {
// // // // 	int i;
// // // // 	i = 0;
// // // // 	//printf("ben: %s\n", s);
// // // // 	while (s[i])
// // // // 	{

// // // // 		if (s[i] == '\'' || s[i] == '\"')
// // // // 		{
// // // // 			i++;
// // // // 			while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] == 32)
// // // // 				i++;
// // // // 			if (s[i + 1] == '\0' && (s[i] == '\'' || s[i] == '\"'))
// // // // 			{
// // // // 				printf("ben: %c\n", s[i]);
// // // // 				return (1);
// // // // 			}
// // // // 		}
// // // // 		i++;
// // // // 	}
// // // // 	return (0);
// // // // }
// // // //i = 0;
// // // 	// while (split_space[i])
// // // 	// {
// // // 	// 	free(split_space[i]);
// // // 	// 	i++;
// // // 	// }

// // // 	// 	free_array(split_space);
// // // 	// free_array(pipe_input);


// // // 	void dolar_mix_assign(t_program *program, t_lexer *parser_input)
// // // {
// // // 	char *p_inputiz;

// // // 	char q_type;
// // // 	int i = 0;
// // // 	int dolar = 0;
// // // 	int j = 0;
// // // 	int k = 0;
// // // 	//$HOME"'$HOME'"$HOME"
// // // 	p_inputiz = parser_input->cmd;
// // // 	program->d_cmd = (t_lexer **)malloc(sizeof(t_lexer *) * (d_count_cmd(program, p_inputiz) + 1));

// // // 	if (!program->d_cmd)
// // // 		error_message("memory allocation");

// // // 	while (p_inputiz[i])
// // // 	{
// // // 		if (p_inputiz[i] == '\'' || p_inputiz[i] == '\"')
// // // 		{
// // // 			q_type = p_inputiz[i];
// // // 			i++;
// // // 			// if (is_multi_dolar(p_inputiz + i, q_type) > 1)
// // // 			// {
// // // 			program->d_cmd[k] = (t_lexer *)malloc(sizeof(t_lexer));
// // // 			if (!program->d_cmd[k])
// // // 				error_message("memory allocation");

// // // 			program->d_cmd[k]->cmd = (char *)malloc(sizeof(char) * 256);
// // // 			j = 0;

// // // 			program->d_cmd[k]->cmd[j++] = q_type;
// // // 			while (p_inputiz[i] && p_inputiz[i] != q_type)
// // // 			{
// // // 				program->d_cmd[k]->cmd[j] = p_inputiz[i];
// // // 				j++;
// // // 				i++;
// // // 			}
// // // 			if (p_inputiz[i] == q_type)
// // // 			{
// // // 				program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // // 			}
// // // 			program->d_cmd[k]->cmd[j] = '\0';

// // // 			k++;
// // // 		}
// // // 		// a"'$HOME'$HOME"$H'O'ME"$HOME"
// // // 		//  23.home 'un nasıl durduğunu anlamak için tırnak ve sonrasında dolar varsa yeni bir
// // // 		// dolara geçtin daha doldurma dur de

// // // 		//$HOME$HOME

// // // 		else
// // // 		{
// // // 			j = 0;
// // // 			program->d_cmd[k] = (t_lexer *)malloc(sizeof(t_lexer));
// // // 			if (!program->d_cmd[k])
// // // 				error_message("memory allocation");
// // // 			program->d_cmd[k]->cmd = (char *)malloc(sizeof(char) * 256);

// // // 			// printf(" input %s", program->d_cmd[k]->cmd);
// // // 			dolar = 0;
// // // 			while (p_inputiz[i] && p_inputiz[i] != '\'' && p_inputiz[i] != '\"' && dolar == 0)
// // // 			{
// // // 				if (p_inputiz[i] == 36)
// // // 				{

// // // 					program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // // 					dolar = 1;
// // // 					while (p_inputiz[i] != '\0' && p_inputiz[i] != 36)
// // // 					{
// // // 						program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // // 					}
// // // 					if(p_inputiz[i] != '\0'&& p_inputiz[i] != '\'' && p_inputiz[i] != '\"')
// // // 						program->d_cmd[k]->cmd[j++] = p_inputiz[i++];

					
// // // 				}
// // // 				else if(p_inputiz[i])

// // // 					program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // // 			}

// // // 			program->d_cmd[k]->cmd[j] = '\0';
// // // 			//printf("dizi:%s\n", program->d_cmd[k]->cmd);
// // // 			k++;
// // // 		}

// // // 		// else
// // // 		// {
// // // 		// 	j = 0;
// // // 		// 	program->d_cmd[k] = (t_lexer *)malloc(sizeof(t_lexer));
// // // 		// 	if (!program->d_cmd[k])
// // // 		// 		error_message("memory allocation");

// // // 		// 	program->d_cmd[k]->cmd = (char *)malloc(sizeof(char) * 256);

// // // 		// 	program->d_cmd[k]->cmd[j] = p_inputiz[i];
// // // 		// 	printf("sonra: %c\n", program->d_cmd[k]->cmd[j]);
// // // 		// 	i++;
// // // 		// 	j++;
// // // 		// 	program->d_cmd[k]->cmd[j] = '\0';
// // // 		// 	// k++;
// // // 		// }
// // // 	}

// // // 	printf("k: %d\n", k);
// // // 	program->d_cmd[k] = NULL;
// // // 	k = 0;

// // // 	while (program->d_cmd[k] != NULL)
// // // 	{

// // // 		printf("%s\n", program->d_cmd[k]->cmd);
// // // 		if (program->d_cmd[k]->cmd)
// // // 			k++;
// // // 	}
// // // 	exit(1);
// // // }


// // void	dolar_mix_assign(t_program *program, t_lexer *parser_input)
// // {
// // 	char	*p_inputiz;
// // 	char	q_type;
// // 	int		i;
// // 	int		dolar;
// // 	int		j;
// // 	int		k;

// // 	i = 0;
// // 	dolar = 0;
// // 	j = 0;
// // 	k = 0;
// // 	p_inputiz = parser_input->cmd;
// // 	program->d_cmd = (t_lexer **)malloc(sizeof(t_lexer *)
// // 			* (d_count_cmd(program, p_inputiz) + 1));
// // 	if (!program->d_cmd)
// // 		error_message("memory allocation");
// // 	while (p_inputiz[i])
// // 	{
// // 			program->d_cmd[k] = (t_lexer *)malloc(sizeof(t_lexer));
// // 			if (!program->d_cmd[k])
// // 				error_message("memory allocation");
// // 			program->d_cmd[k]->cmd = (char *)malloc(sizeof(char) * 256);

			
// // 		if (p_inputiz[i] == '\'' || p_inputiz[i] == '\"')
// // 		{
// // 			q_type = p_inputiz[i];
// // 			i++;
// // 			j = 0;
// // 			program->d_cmd[k]->cmd[j++] = q_type;
// // 			while (p_inputiz[i] && p_inputiz[i] != q_type)
// // 			{
// // 				program->d_cmd[k]->cmd[j] = p_inputiz[i];
// // 				j++;
// // 				i++;
// // 			}
// // 			if (p_inputiz[i] == q_type)
// // 			{
// // 				program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // 			}
// // 			program->d_cmd[k]->cmd[j] = '\0';
// // 			k++;
// // 		}
// // 		else
// // 		{
// // 			j = 0;
// // 			dolar = 0;
// // 			while (p_inputiz[i] && p_inputiz[i] != '\'' && p_inputiz[i] != '\"'
// // 				&& dolar == 0)
// // 			{
// // 				if (p_inputiz[i] == 36)
// // 				{
// // 					program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // 					dolar = 1;
// // 					while (p_inputiz[i] != '\0' && p_inputiz[i] != 36)
// // 					{
// // 						program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // 					}
// // 					if (p_inputiz[i] != '\0' && p_inputiz[i] != '\''
// // 						&& p_inputiz[i] != '\"')
// // 						program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // 				}
// // 				else if (p_inputiz[i])
// // 					program->d_cmd[k]->cmd[j++] = p_inputiz[i++];
// // 			}
// // 		}
// // 		program->d_cmd[k]->cmd[j] = '\0';
// // 		k++;
// // 	}
// // 	program->d_cmd[k] = NULL;
// // 	k = 0;
// // 	while (program->d_cmd[k] != NULL)
// // 	{
// // 		printf("%s\n", program->d_cmd[k]->cmd);
// // 		if (program->d_cmd[k]->cmd)
// // 			k++;
// // 	}
// // 	exit(1);
// // }
// // void	quote_clean(t_program *program)
// // {
// // 	int	i;
// // 	int	j;

// // 	i = 0;
// // 	j = 0;
// // 	while (program->parser_input[i])
// // 	{
// // 		j = 0;
// // 		while (program->parser_input[i][j])
// // 		{
// // 			if (program->parser_input[i][j]->key == 5
// // 				&& count_dolar(program->parser_input[i][j]->cmd) > 1)
// // 				dolar_mix_assign(program, program->parser_input[i][j]);
// // 			zi_striteri(program->parser_input[i][j], f);
// // 			// printf("iteri:%s",program->parser_input[i][j]->cmd);
// // 			if (program->parser_input[i][j]->key == 5
// // 				&& count_dolar(program->parser_input[i][j]->cmd) == 1)
// // 				loc_dolar(program, program->parser_input[i][j]);
// // 			printf("-----------command:%d: arg:%d:%s  key:%d\n", i, j,
// // 				program->parser_input[i][j]->cmd,
// // 				program->parser_input[i][j]->key);
// // 			j++;
// // 		}
// // 		i++;
// // 	}
// // }

// // //  echo "$HOME"'$HOME''"$HOME"' birden fazla dolarlı ise dolar olarak
// // // setle . tırnak temizlerken birden fazla varsa içini tek tek temizle(execde)
// //if (dolar == 1)
// 				// {
// 				// 	program->d_cmd[k]->cmd[j] = '\0';
// 				// 	// printf("3 %s\n", program->d_cmd[k]->cmd);
// 				// 	k++;
// 				// 	j = 0;
// 				// }


// int	d_count_cmd(t_program *program, char *p_input)
// {
// 	char	q_type;
// 	int		i;
// 	int		count;

// 	(void)program;
// 	i = 0;
// 	count = 0;
// 	while (p_input[i])
// 	{
// 		if (p_input[i] == 36)
// 		{
// 			i++;
// 			while (p_input[i] && (p_input[i] != '\'' && p_input[i] != '\"'
// 					&& p_input[i] != 36))
// 				i++;
// 			if (p_input[i] == '\0' || p_input[i] == 36)
// 				count++;
// 			if (p_input[i] == '\'' || p_input[i] == '\"')
// 			{
// 				q_type = p_input[i];
// 				if (!is_env(p_input + i + 1, q_type))
// 					count++;
// 			}
// 		}
// 		else if (p_input[i] == '\'' || p_input[i] == '\"')
// 		{
// 			q_type = p_input[i];
// 			if (!is_env(p_input + i, q_type))
// 				count++;
// 			i++;
// 			while (p_input[i] && (p_input[i] != q_type))
// 				i++;
// 			i++;
// 		}
// 		else if (p_input[i])
// 			i++;
// 	}
// 	return (count);
// }

	//	iz_string=dolar_env(program, iz_string);
	// if(iz_string==NULL)
	//$home temizle
	// 	}
	// 	if (parser_input->cmd[i] == 36 || parser_input->cmd[i] == '\"')
	// 	{
	// 		if (parser_input->cmd[i] == 36)
	// 		{
	// 			j = 0;
	// 			i++;
	// 			// cpy[j] = parser_input->cmd[i];
	// 			while (parser_input->cmd[i])
	// 			{
	// 				if ((parser_input->cmd[i] >= 97
	// 						&& parser_input->cmd[i] >= 122)
	// 					|| (parser_input->cmd[i] >= 48
	// 						&& parser_input->cmd[i] >= 57)
	// 					|| (parser_input->cmd[i] >= 65
	// 						&& parser_input->cmd[i] >= 90))
	// 				{
	// 					cpy[j] = parser_input->cmd[i];
	// 					i++;
	// 				}
	// 			}
	// 			// if( dolar_env(program, cpy)==NULL)
	// 			// {
	// 			// 	iz_string=ft_substr();
	// 			// 	if(iz_string=dolar_env());
	// 			// }
	// 		}
	// 		else if ((parser_input->cmd[i] == '\''
	// 				|| parser_input->cmd[i] == '\"'))
	// 		{
	// 			q_type = parser_input->cmd[i];
	// 		}
	// 		if (q_type == "\"")
	// 		{
	// 			cpy = dolar_env(program, cpy);
	// 			parser_input->cmd[i] = cpy;
	// 			// free(cpy);
	// 		}
	// 		else
	// 			iz_string = parser_input->cmd[i];
	// 	}
	// 	else
	// 		iz_string = parser_input->cmd[i];
	// 	i++;
	// }
	// parser_input->cmd[i] = cpy;
		// else if (parser_input->cmd[i] == '\'')
		// {
		// 	single_start = i;
		// 	i++;
		// 	while (parser_input->cmd[i] && parser_input->cmd[i] != '\'')
		// 		i++;
		// 	s_end = i;
		// 	iz_string = ft_substr(parser_input->cmd, single_start, (s_end
		// 				- single_start) + 1);
		// 	str = ft_strjoin(before_dolar, iz_string);
			
		// }