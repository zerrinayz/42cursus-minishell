NAME= minishell
SRCS= main.c\
	  error.c\
	  free.c\
	  lexer_free.c\
	  init.c\
	  parser/parser.c\
	  parser/p_quote.c\
	  parser/p_pipe.c\
	  parser/p_redirection.c\
	  utils/parser_util.c\
	  utils/parser_util_2.c\
	  lexer/lexer.c\
	  lexer/set_meta.c\
	  lexer/dolar_handler.c\
	  lexer/dolar_handler_2.c\
	  utils/lexer_util.c\
	  builtin/echo.c\
	  builtin/cd.c\
	  builtin/pwd.c\
	  builtin/env.c\
	  builtin/export.c\

OBJS= $(SRCS:.c=.o)
CC= gcc
CFLAGS= -Wall -Wextra -Werror -g -fsanitize=address
RM= rm -rf
LIBFT=./includes/libft/libft.a
READLINE=readline


all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install
	$(RM) readline-8.2 readline-8.2.tar.gz

$(NAME) : $(OBJS)
	make -C ./includes/libft -s
	make bonus -C ./includes/libft -s
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBFT) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

clean:
	make clean -C ./includes/libft -s
	make bonus clean -C ./includes/libft -s
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./includes/libft -s
	make bonus fclean -C ./includes/libft -s
	$(RM) $(NAME)
	$(RM) $(READLINE) readline-8.2 readline-8.2.tar.gz

re: fclean all

.PHONY: all clean fclean re