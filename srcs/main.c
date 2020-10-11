/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:59:51 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/12 01:44:57 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "commands.h"
#include "libftprintf.h"
#include <sys/wait.h>

void		setup_commands(t_shell_cmd commands[7])
{
	(commands)[0] = new_shell_cmd("echo", &dummy_echo);
	(commands)[1] = new_shell_cmd("cd", &dummy_cd);
	(commands)[2] = new_shell_cmd("export", &dummy_export);
	(commands)[3] = new_shell_cmd("unset", &dummy_unset);
	(commands)[4] = new_shell_cmd("env", &dummy_env);
	(commands)[5] = new_shell_cmd("exit", &dummy_exit);
	(commands)[6] = new_shell_cmd("pwd", &dummy_pwd);
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
			*command_flag = i;
			*command = parse(tokens);
			//print_commands(*command);
			break ;
		}
	}
}

int			main(int argc, char **argv, char **environ)
{
	pid_t		id;
	t_list		*env;
	char		*line;
	char		**tokens;
	int			command_flag;
	t_command	command;

	if (argc)
		argc = 0;
	if (argv)
		argv = 0;
	env = NULL;
	ft_putstr_fd("You're finally awake!\n", 1);
	setup_commands(g_commands);
	ft_get_env(&env, environ);
	while (1)
	{
		ft_putstr_fd("bibaibobabash-0.0.2$ ", 1);
		if (get_next_line(0, &line))
		{
			init_command(&command);
			tokens = tokenize(line);
			if (!tokens)
				continue ;
			expand(&tokens, env);
			command_flag = -1;
			get_command(&command, &command_flag, tokens);
			command_flag = -1;
			if (command_flag < 0)
			{
				if (!(id = fork()))
				{
					if (execve(tokens[0], tokens, environ) < 0)
					{
						if (execve(ft_strjoin("executables/", tokens[0]), tokens, environ) < 0) // leak here
						{
							ft_putstr_fd(tokens[0], 2);
							ft_putstr_fd(": command not found\n", 2);
							exit (127);
						}
					}
					exit (0);
				}
				else
					wait(&g_status);
			}
			else
			{
				if (!(id = fork()))
				{
					g_commands[command_flag].function(command);
				}
				else
					wait(&g_status);
			}
			g_status = (g_status & 0xff00) >> 8;
			free(line);
			free_command(&command);
			clear_tokens(tokens, -1);
		}
	}
	return (0);
}
