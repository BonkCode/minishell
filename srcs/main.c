/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:38:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 14:35:08 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "commands.h"
#include "../libft/libftprintf.h"

void		setup_commands(t_shell_cmd commands[7])
{
	(commands)[0] = new_shell_cmd("echo", &dummy_echo);
	(commands)[1] = new_shell_cmd("cd", &dummy_cd);
	(commands)[2] = new_shell_cmd("export", &dummy_export);
	(commands)[3] = new_shell_cmd("unset", &dummy_unset);
	(commands)[4] = new_shell_cmd("env", &dummy_env);
	(commands)[5] = new_shell_cmd("exit", &dummy_exit);
	(commands)[6] = new_shell_cmd("pwd", &dummy_exit);
}

t_shell_cmd	g_commands[7];
int			g_status = 0;

char		**lex(char *line)
{
	char **tokens;

	tokens = ft_split(line, ' ');
	return (tokens);
}

void		init_command(t_command *command)
{
	command->status = 127;
	command->infile = NULL;
	command->errfile = NULL;
	command->outfile = NULL;
	command->commands = NULL;
}

void		get_command(t_command *command, int *command_flag, char **tokens)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strncmp(tokens[0], g_commands[i].name,
				ft_strlen(g_commands[i].name) + 1) == 0)
		{
			*command_flag = 1;
			*command = parse(tokens, g_commands);
			print_commands(*command);
			break ;
		}
	}
}

int			main(void)
{
	char		*line;
	char		**tokens;
	int			command_flag;
	t_command	command;

	setup_commands(g_commands);
	while (1)
	{
		ft_putstr_fd("bibaibobabash-0.0.2$ ", 1);
		if (get_next_line(0, &line))
		{
			init_command(&command);
			tokens = tokenize(line);
			command_flag = 0;
			get_command(&command, &command_flag, tokens);
			if (!command_flag)
				ft_putstr_fd("wrong command", 2);
			ft_putstr_fd("\n", 1);
			free(line);
			free_command(&command);
			clear_tokens(tokens, -1);
		}
	}
	return (0);
}
