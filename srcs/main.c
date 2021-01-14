/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:59:51 by rvernius          #+#    #+#             */
/*   Updated: 2021/01/14 20:26:47 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "commands.h"
#include <signal.h>
#include "libftprintf.h"
#include <sys/wait.h>

t_shell_cmd	g_commands[7];
int			g_status = 0;

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
			return ;
		}
	}
	*command = parse(tokens);
}

char	*g_line;

void		sigint_handler(int s)
{
	if (g_line)
	{
		free(g_line);
		g_line = NULL;
	}
	g_status = 130;
	ft_putstr_fd("\nbibaibobabash-1.0.0$ ", 1);
	s = s;
}

int		g_start_env_len;

static void	launch_minishell(char **environ)
{
	int	read_res;

	while (1)
	{
		ft_putstr_fd("bibaibobabash-0.0.2$ ", 1);
		if ((read_res = get_next_line_no_eof(0, &g_line)))
		{
			handle_line(&g_line, environ);
		}
		else
		{
			if (*g_line == '\0' && read_res == 0)
			{
				free(g_line);
				ft_putstr_fd("\n", 1);
				exit(0);
			}
		}
	}
}

int			main(int argc, char **argv, char **environ)
{
	g_start_env_len = 0;
	while (environ[g_start_env_len])
		++g_start_env_len;
	g_line = NULL;
	if (argc)
		argc = 0;
	if (argv)
		argv = 0;
	ft_putstr_fd("You're finally awake!\n", 1);
	setup_commands(g_commands);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	launch_minishell(environ);
	return (0);
}
