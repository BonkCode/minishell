/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:59:51 by rvernius          #+#    #+#             */
/*   Updated: 2020/12/21 23:53:23 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "commands.h"
#include <signal.h>
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
	(commands)[6] = new_shell_cmd("pwd", &ft_pwd);
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
	command->piped = 0;
	command->append = 0;
	command->infile = NULL;
	command->errfile = NULL;
	command->outfile = NULL;
	command->other_files = NULL;
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
			return ;
		}
	}
	*command = parse(tokens);
}

int			count_non_blanks(char **tokens)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (tokens[++i])
		++size;
	i = -1;
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], "", 1))
			size -= 2;
		else if (!ft_strncmp(tokens[i], " ", 2))
			size -= 1;
	}
	return (size);
}

static void	copy_non_empty(char ***tokens, int size)
{
	int		i;
	char	**temp_2;

	if (!(temp_2 = ft_calloc(sizeof(char *), (size / 2 + 2))))
	{
		clear_tokens(*tokens, -1);
		return ;
	}
	i = -1;
	size = -1;
	while ((*tokens)[++i])
	{
		if (ft_strncmp((*tokens)[i], "", 1))
		{
			if (!(temp_2[++size] = ft_strdup((*tokens)[i])))
			{
				clear_tokens(temp_2, size);
				break ;
			}
		}
	}
	clear_tokens(*tokens, -1);
	*tokens = temp_2;
}

void		glue_2_tokens(char ***tokens, int *i)
{
	char	*temp;

	if (ft_strncmp_split((*tokens)[*i], "; | < > >>", ' ') &&
		(*tokens)[*i + 1] &&
		ft_strncmp_split((*tokens)[*i + 2], "; | < > >>", ' '))
	{
		temp = (*tokens)[*i + 2];
		(*tokens)[*i + 2] = ft_strjoin((*tokens)[*i], (*tokens)[*i + 2]);
		free(temp);
		temp = (*tokens)[*i];
		(*tokens)[*i] = ft_strdup("");
		free(temp);
	}
}

void		glue_tokens(char ***tokens)
{
	char	*temp;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while ((*tokens)[++i])
		++size;
	i = 0;
	while (i < size - 1 && (*tokens)[i])
	{
		if (ft_strncmp((*tokens)[i + 1], " ", 2))
			glue_2_tokens(tokens, &i);
		else
		{
			temp = (*tokens)[i + 1];
			(*tokens)[i + 1] = ft_strdup("");
			free(temp);
		}
		i += 2;
	}
	copy_non_empty(tokens, size);
}

char	*g_line;

void		sigint_handler()
{
	if (g_line)
	{
		free(g_line);
		g_line = NULL;
	}
	g_status = 130;
	ft_putstr_fd("\nbibaibobabash-0.0.2$ ", 1);
}

int			main(int argc, char **argv, char **environ)
{
	int		read_res;

	g_line = NULL;
	if (argc)
		argc = 0;
	if (argv)
		argv = 0;
	ft_putstr_fd("You're finally awake!\n", 1);
	setup_commands(g_commands);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_putstr_fd("bibaibobabash-0.0.2$ ", 1);
		if (read_res = get_next_line(0, &g_line))
		{
			handle_line(&g_line, environ);
		}
		else
		{
			if (*g_line == '\0' && read_res == 0)
			{
				free (g_line);
				ft_putstr_fd("\n", 1);
				exit(0);
			}
		}
	}
	return (0);
}
