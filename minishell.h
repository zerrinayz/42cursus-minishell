/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerrinayaz <zerrinayaz@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:28 by itulgar           #+#    #+#             */
/*   Updated: 2024/10/14 17:46:45 by zerrinayaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define IN_HERADOC 2

#include <stdio.h>
#include "includes/libft/libft.h"
#include "readline/include/readline/history.h"
#include "readline/include/readline/readline.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

enum set_meta
{
	// Append = 0,
	// Heredoc = 1,
	// Input = 2,
	// Output = 3,
	Tilde = 4,
	Dolar = 5,
	S_Dolar = 6,
	Redirect = 7,
};

int global_signal;

typedef struct s_lexer
{
	char *cmd;
	int key;
} t_lexer;

typedef struct s_process
{
	pid_t pid;
	int fd[2];

} t_process;

typedef struct s_program
{
	t_list *envp_list;
	t_list *export_list;
	t_list *lexer_list;
	char *input;
	t_lexer ***parser_input;
	int export_flag;
	int check_quote;
	int control_q_split;
	int control_p_split;
	int unset_flag;
	t_process *process;
	int p_count;
	char **cmd;
	int hd_count;
} t_program;

int error_message(char *str);
void ft_init_program(t_program *program, char **envp);
void free_array(char **tmp);
int ft_parser(t_program *program, char *input);
int p_quote(t_program *program, char *input);
int p_pipe(t_program *program, char *input);
int p_redirection(t_program *program, char *input);
char **zi_split(t_program *program, char *s, char c, int redirect);
char *walk_string(t_program *program, char *s, char c, int redirect);
int zi_count_string(char *s, char c, int redirect);
void free_program(t_program *program);
void free_parser_input(t_program *program);
int set_meta(t_program *program, char *meta);
void print_list(t_list *list);
int zi_strrchr(const char *s, int c, int i);
void quote_clean(t_program *program);
char *zi_strlcpy(char *dst, const char *src, size_t dstsize);
void zi_striteri(t_lexer *s, void f(t_lexer *));
char *in_quote_string(char *s, char c);
size_t zi_strlen(const char *s, char c, int dhand);
char *dolar_env(t_program *program, char *parser_input);
void dolar_free(char *env_str, char *after_dolar);
void dolar_handler(t_program *program, t_lexer *parser_input);
char *env_count_str(t_lexer *parser_input, int *i);
void echo(char **cmd);
void pwd(void);
void cd(t_program *program, char **cmd);
void env(t_program *program, char **cmd);
void export(t_program *program, char **cmd);
void zi_unset(t_program *program, char **cmd);
void search_set_env(t_program *program, char *key, char *content);
int check_identifier(char *parser_input);
void zi_exec(t_program *program);
void redirect(t_program *program, int *i);
int redirect_c(t_program *program, int *i);
int pipe_count(t_program *program);
char *zi_sec_strlcpy(char *dst, const char *src, size_t dstsize);
void signal_handler(int sig);
void heredoc(char *s);
int heredoc_count(t_program *program);
void heredoc_run(t_program *program);
void go_redirect(t_program *program, void run_redirect(char *),
				 char key, int *i, int *j, int split_rd);
int zi_redirectchr(const char *s, char c);
int heredoc_count(t_program *program);
void equal_in_export(t_program *program, char *cmd, int *i);
#endif