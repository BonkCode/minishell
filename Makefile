# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:18:03 by rtrant            #+#    #+#              #
#    Updated: 2020/10/08 17:29:52 by rvernius         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c \
		srcs/shell_cmd_const.c \
		srcs/lexer/tokenize.c \
		srcs/lexer/tokens_clearer.c \
		srcs/parser/parse.c \
		srcs/t_commands/command_clearer.c \
		srcs/commands/dummy/one.c \
		srcs/commands/dummy/two.c \
		srcs/print_2d.c \
		srcs/t_commands/command_printer.c \
		srcs/t_commands/constructor.c \
		srcs/utils/parse_utils.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror -Ilibft -Iheaders -L.

all: $(NAME)

$(NAME):
	@echo "Compiling libftprintf"
	@$(MAKE) -C libft bonus >/dev/null
	@mv libft/libft.a .
	@gcc $(FLAGS) -o $(NAME) $(SRCS) libft.a
	@$(MAKE) clean >/dev/null

clean:
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf minishell libft.a

re: fclean all

norme:
	norminette $(SRCS) headers/*.h

.PHONY: all clean fclean re norme