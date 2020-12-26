# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:18:03 by rtrant            #+#    #+#              #
#    Updated: 2020/12/27 01:56:55 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c \
		srcs/shell_cmd_const.c \
		srcs/lexer/tokenize.c \
		srcs/lexer/tokens_clearer.c \
		srcs/parser/parse.c \
		srcs/t_commands/command_clearer.c \
		srcs/commands/dummy/raw_dummy_1.c \
		srcs/commands/dummy/raw_dummy_2.c \
		srcs/print_2d.c \
		srcs/t_commands/command_printer.c \
		srcs/t_commands/constructor.c \
		srcs/utils/parse_utils.c \
		srcs/expander/expander.c \
		srcs/commands/env/ft_get_env.c \
		srcs/expander/expander_utils.c \
		srcs/utils/clearing_utils.c \
		srcs/lexer/tokens_splitter.c \
		srcs/executor/executor.c \
		srcs/validator/validator.c \
		srcs/bonk_commands/echo/echo.c \
		srcs/bonk_commands/cd/cd.c \
		srcs/bonk_commands/pwd/pwd.c \
		srcs/bonk_commands/env/env.c \
		srcs/bonk_commands/exit/exit.c \
		srcs/bonk_commands/export/export.c

NAME = minishell

FLAGS = -Ilibft -Iheaders -L.

all: $(NAME)

$(NAME):
	@echo "Compiling libftprintf"
	@$(MAKE) -C libft bonus >/dev/null
	@mv libft/libft.a .
	@echo "Compiling minishell"
	@gcc $(FLAGS) -o $(NAME) $(SRCS) libft.a
	@$(MAKE) clean >/dev/null

dummy:
	@echo "Creating dummy exec files"
	@gcc srcs/commands/dummy/dummy_cd.c -o executables/cd
	@gcc srcs/commands/dummy/dummy_echo.c -o executables/echo
	@gcc srcs/commands/dummy/dummy_env.c -o executables/env
	@gcc srcs/commands/dummy/dummy_exit.c -o executables/exit
	@gcc srcs/commands/dummy/dummy_export.c -o executables/export
	@gcc srcs/commands/dummy/dummy_unset.c -o executables/unset
	@gcc srcs/commands/dummy/dummy_pwd.c -o executables/pwd

clean:
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf minishell libft.a executables/*

re: fclean all

norme:
	norminette $(SRCS) headers/*.h

.PHONY: all clean fclean re norme dummy