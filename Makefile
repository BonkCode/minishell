# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:18:03 by rtrant            #+#    #+#              #
#    Updated: 2020/10/06 12:55:36 by rvernius         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c \
		srcs/shell_cmd_const.c \
		srcs/lexer/tokenize.c \
		srcs/parser/parse.c \
		srcs/t_commands/command_clearer.c

NAME = minishell

FLAGS = -Ilibft -Iheaders -Ift_printf -L.

all: $(NAME)

$(NAME):
	@echo "Compiling libftprintf"
	@$(MAKE) -C libft bonus >/dev/null
	@mv libft/libft.a .
	@gcc $(FLAGS) -o $(NAME) $(SRCS) libft.a
	@$(MAKE) clean >/dev/null

clean:
	@$(MAKE) -C libft clean >/dev/null

fclean: clean
	rm -rf minishell libft.a

re: fclean all

.PHONY: all clean fclean re