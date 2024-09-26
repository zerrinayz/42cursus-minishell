/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:28 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/25 19:23:33 by itulgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "includes/libft/libft.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/readline.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

enum		set_meta
{
	Append = 0,
	Heredoc = 1,
	Input = 2,
	Output = 3,
	Tilde = 4,
	Dolar = 5,
	S_Dolar = 6,
};

int			global_signal;
typedef struct s_lexer
{
	char	*cmd;
	int		key;
}			t_lexer;



typedef struct s_program
{
	t_list	*envp_list;
	t_list	*lexer_list;
	char	*input;
	t_lexer	***parser_input;
	t_lexer **d_cmd;
	int		check_quote;
	int		control_q_split;
	int		control_p_split;
}			t_program;

int			error_message(char *str);
void		ft_init_program(t_program *program, char **envp);
void		free_array(char **tmp);
void		init_signal(void);
int			ft_parser(t_program *program, char *input);
int			p_quote(t_program *program, char *input);
int			p_pipe(t_program *program, char *input);
int			p_redirection(t_program *program, char *input);
char		**zi_split(t_program *program, char *s, char c);
char		*walk_to_quote_pipe(t_program *program, char *s, char c);
char		*walk_to_pipe(t_program *program, char *s, char c);
char		*walk_string(t_program *program, char *s, char c);
int			count_string(char *s, char c);
void		free_program(t_program *program);
void		free_parser_input(t_program *program);

int			set_meta(t_program *program, char *meta);
void		print_list(t_list *list);
int			zi_strrchr(const char *s, int c, int i);
void		quote_clean(t_program *program);
char		*zi_strlcpy(char *dst, const char *src, size_t dstsize);
void		zi_striteri(t_lexer *s, void f(t_lexer *));
char		*in_quote_string(char *s, char c);
int	d_count_cmd(t_program *program, char *p_input);
	int count_dolar(char *parser_input);
void		loc_dolar(t_program *program, t_lexer *parser_inputi);
char		*get_env(t_program *program, char *parser_input, char c);
size_t		zi_strlen(const char *s, char c);
void		dolar_mix_assign(t_program *program, t_lexer *parser_input);
int	is_env(char *parser_input, char quote_type);
#endif