# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:18:03 by rtrant            #+#    #+#              #
#    Updated: 2020/10/03 17:09:49 by rtrant           ###   ########.fr        #
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
	@echo "Compiling libft"
	@$(MAKE) -C libft bonus >/dev/null
	@mv libft/libft.a .
	@echo "Compiling libftprintf"
	@$(MAKE) -C ft_printf > /dev/null
	@mv ft_printf/libftprintf.a .
	@gcc $(FLAGS) -o $(NAME) $(SRCS) libft.a libftprintf.a
	@$(MAKE) clean >/dev/null

clean:
	@$(MAKE) -C libft clean >/dev/null
	@$(MAKE) -C ft_printf clean >/dev/null

fclean: clean
	rm -rf minishell libft.a libftprintf.a

re: fclean all

.PHONY: all clean fclean re