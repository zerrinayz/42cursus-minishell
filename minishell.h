/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itulgar < itulgar@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:28 by itulgar           #+#    #+#             */
/*   Updated: 2024/09/15 20:27:12 by itulgar          ###   ########.fr       */
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

int			global_signal;
typedef struct s_program
{
	t_list	*envp_list;
	char	***parser_input;
	char	*input;
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
int			p_pipe(char *input);
int			p_redirection(char *input);
char		**zi_split(t_program *program, char *s, char c);
char		*walk_to_quote_pipe(t_program *program, char *s, char c);
char		*walk_to_pipe(t_program *program, char *s, char c);
char		*walk_string(t_program *program, char *s, char c);
int			count_string(char *s, char c);
#endif