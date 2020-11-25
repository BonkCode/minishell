/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:09:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/11/25 22:12:49 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "commands.h"
#include "libftprintf.h"
#include <sys/wait.h>

extern int			g_status;
extern t_shell_cmd	g_commands[7];

static void	run_command(int command_flag, t_command command)
{
	pid_t	id;

	if (!(id = fork()))
	{
		exit (0);
		g_commands[command_flag].function(command);
	}
	else
		wait(&g_status);
}

static	void		del(void *data)
{
	if (data)
		free(data);
	data = NULL;
}

static void	run_executable(char **split_tokens, char **environ)
{
	pid_t	id;
	
	if (!(id = fork()))
	{
		if (execve(split_tokens[0],
					split_tokens, environ) < 0 &&
			execve(ft_strjoin("/bin/", split_tokens[0]), // leak here
					split_tokens, environ) < 0)
		{
			ft_putstr_fd(split_tokens[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		exit(0);
	}
	else
		wait(&g_status);
}

void		execute(char ****split_tokens, t_list *env, char **environ, int i)
{
	t_command			command;
	int					command_flag;
	t_simple_command	*s_c;
	
	init_command(&command);
	expand(&(*split_tokens)[i], env);
	glue_tokens(&(*split_tokens)[i]);
	//print_2d(split_tokens[i]);
	//ft_putchar_fd('\n', 1);
	command_flag = -1;
	get_command(&command, &command_flag, (*split_tokens)[i]);
	s_c = command.commands;
	//print_commands(command);
	//ft_putstr_fd("\n\n", 1);
	while (command.commands)
	{
		if (command_flag < 0)
			run_executable((*split_tokens)[i], environ);
		else
			run_command(command_flag, command);
		g_status = (g_status & 0xff00) >> 8;
		command.commands = command.commands->next;
	}
	command.commands = s_c;
	free_command(&command);
}

void		handle_line(char **line, char **environ)
{
	pid_t				id;
	t_list				*env;
	char				**tokens;
	char				***split_tokens;
	int					i;
	
	tokens = NULL;
	split_tokens = NULL;
	env = NULL;
	
	ft_get_env(&env, environ);
	tokens = tokenize(*line);
	if (!tokens)
		return ;
	i = -1;
	//print_2d(tokens);
	//ft_putchar_fd('\n', 1);
	if (!(split_tokens = split_tokens_by_semicolons(tokens)))
	{
		clear_tokens(tokens, -1);
		ft_lstclear(&env, free);
		free(*line);
		return ;
	}
	i = -1;
	while (split_tokens[++i])
	{
		execute(&split_tokens, env, environ, i);
	}
	free(*line);
	ft_lstclear(&env, del);
	clear_tokens(tokens, -1);
	clear_3d(&split_tokens, -1, -1);
}