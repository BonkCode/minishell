# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:18:03 by rtrant            #+#    #+#              #
#    Updated: 2020/10/10 17:03:20 by rtrant           ###   ########.fr        #
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
		srcs/utils/parse_utils.c \
		srcs/expander/expander.c \
		srcs/commands/env/ft_get_env.c \
		srcs/expander/expander_utils.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

FLAGS = -Wall -Wextra -Werror -Ilibft -Iheaders -L.

all: $(NAME)

$(NAME):
	@echo "Compiling libftprintf"
	@$(MAKE) -C libft bonus >/dev/null
	@mv libft/libft.a .
	@gcc $(FLAGS) -o $(NAME) $(OBJS) libft.a
	@$(MAKE) clean >/dev/null

%.o : %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf minishell libft.a

re: fclean all

norme:
	norminette $(SRCS) headers/*.h

.PHONY: all clean fclean re norme