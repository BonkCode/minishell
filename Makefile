# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 16:18:03 by rtrant            #+#    #+#              #
#    Updated: 2021/01/07 20:04:50 by rtrant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/main.c \
		srcs/shell_cmd_const.c \
		srcs/lexer/tokenize.c \
		srcs/lexer/tokens_clearer.c \
		srcs/parser/parse.c \
		srcs/t_commands/command_clearer.c \
		srcs/t_commands/constructor.c \
		srcs/utils/parse_utils.c \
		srcs/expander/expander.c \
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
		srcs/bonk_commands/export/export.c \
		srcs/bonk_commands/unset/unset.c \
		srcs/bonk_commands/export/export_utils.c \
		srcs/utils/utils.c \
		srcs/executor/executor_utils/redirect_stdout.c \
		srcs/executor/executor_utils/redirect_stderr.c \
		srcs/executor/executor_utils/return_error.c \
		srcs/executor/executor_utils/fd_trickery.c \
		srcs/executor/executor_utils/launchers/builtin.c \
		srcs/executor/executor_utils/launchers/exec.c \
		srcs/executor/executor_utils/pipe_stuff.c \
		srcs/executor/executor_utils/redirect_stdin.c \
		srcs/executor/executor_utils/redirect_other.c \
		srcs/glue/glue.c \
		srcs/setup_shell_cmd.c \
		srcs/bonk_commands/ft_get_env.c

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

clean:
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf minishell libft.a executables/*

re: fclean all

norme:
	norminette $(SRCS) headers/*.h libft/*.c libft/*.h

.PHONY: all clean fclean re norme dummy