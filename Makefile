SRCS = 	srcs/main.c \
		srcs/shell_cmd_const.c \
		srcs/lexer/tokenize.c \
		srcs/parser/parse.c \
		srcs/t_commands/command_clearer.c

NAME = minishell

FLAGS = -Ilibft -Iheaders -L.

all: $(NAME)

$(NAME):
	$(MAKE) -C libft bonus
	mv libft/libft.a .
	gcc $(FLAGS) -o $(NAME) $(SRCS) libft.a
	$(MAKE) clean

clean:
	$(MAKE) -C libft clean

fclean: clean
	rm -rf minishell libft.a

re: fclean all

.PHONY: all clean fclean re