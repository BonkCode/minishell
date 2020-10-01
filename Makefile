SRCS = 	srcs/main.c \
		srcs/shell_cmd_const.c \
		srcs/lexer/tokenize.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror -Ilibft -Iheaders -L.

all: $(NAME)

$(NAME):
	$(MAKE) -C libft
	mv libft/libft.a .
	gcc $(FLAGS) -o $(NAME) $(SRCS) libft.a

clean:
	$(MAKE) -C libft clean

fclean: clean
	rm -rf minishell libft.a

re: fclean all

.PHONY: all clean fclean re