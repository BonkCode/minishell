/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:09:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/22 00:50:08 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "commands.h"
#include <fcntl.h>
#include "libftprintf.h"
#include <signal.h>
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

static void	sigint_skip()
{
	write(1, "\n", 1);
}

static char	**form_args(t_list *args)
{
	char	**return_args;
	int		i;
	
	i = -1;
	return_args = ft_calloc(ft_lstsize(args) + 1, sizeof(char *));
	while (args)
	{
		return_args[++i] = ft_strdup(args->content);
		args = args->next;
	}
	return (return_args);
}

t_list		*get_path(char **environ)
{
	int		i;
	t_list	*env;
	t_list	*path;
	char	**split_var;
	char	**paths;
	
	ft_get_env(&env, environ);
	while (env)
	{
		split_var = ft_split(env->content, '=');
		if (!ft_strncmp(split_var[0], "PATH", 5))
			break ;
		env = env->next;
	}
	path = ft_lstnew(ft_strdup(""));
	paths = ft_split(split_var[1], ':');
	
	i = -1;
	while (paths[++i])
		ft_lstadd_back(&path, ft_lstnew(ft_strdup(paths[i])));
	clear_tokens(paths, -1);
	clear_tokens(split_var, -1);
	return (path);
}

static void	run_executable(t_simple_command *command, char **environ)
{
	pid_t	id;
	char	**args;
	t_list	*path;
	int		executed;
	char	*temp_path;

	executed = -1;
	args = form_args(command->args);
	signal(SIGINT, sigint_skip);
	//ft_printf("ARGS:\n");
	//print_2d(args);
	path = NULL;
	if (!(id = fork()))
	{
		path = get_path(environ);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (path)
		{
			temp_path = ft_strjoin(path->content, "/");
			if ((executed = execve(ft_strjoin(temp_path, command->command), args, environ)) >= 0)
				break ;
			free(temp_path);
			path = path->next;
		}
		if (executed < 0)
		{
			ft_putstr_fd(command->command, 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_lstclear(&path, del);
			exit(127);
		}
		free(temp_path);
		ft_lstclear(&path, del);
		exit(0);
	}
	else
	{
		wait(&g_status);
	}
	signal(SIGINT, sigint_handler);
}

void		execute(char ****split_tokens, t_list *env, char **environ, int i)
{
	t_command			command;
	int					command_flag;
	t_simple_command	*s_c;
	int					std_copy[2];
	int					pipe_fd[2];
	int					pipe_fd_dup[2];
	
	init_command(&command);
	expand(&(*split_tokens)[i], env);
	//print_2d((*split_tokens)[i]);
	glue_tokens(&(*split_tokens)[i]);
//	print_2d((*split_tokens)[i]);
	//ft_putchar_fd('\n', 1);
	command_flag = -1;
	//print_2d((*split_tokens)[i]);
	get_command(&command, &command_flag, (*split_tokens)[i]);
	s_c = command.commands;
	//print_commands(command);
	//ft_putstr_fd("\n\n", 1);
	if (command.piped)
	{
		pipe(pipe_fd);
		std_copy[0] = dup(0);
		std_copy[1] = dup(1);
		pipe_fd_dup[0] = dup2(pipe_fd[0], 0);
		pipe_fd_dup[1] = dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	while (command.commands)
	{
		if (command.piped && !command.commands->next)
		{
			dup2(std_copy[1], 1);
			close (std_copy[1]);
		}
		if (command_flag < 0)
		{
			run_executable(command.commands, environ);
		}
		else
			run_command(command_flag, command);
		g_status = (g_status & 0xff00) >> 8;
		command.commands = command.commands->next;
	}
	if (command.piped)
	{
		dup2(std_copy[0], 0);
		close(std_copy[0]);
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
	{
		if ((*line)[0])
			ft_printf("NO CLOSE QMARKS\n");
		return ;
	}
	if (validate_tokens(tokens))
	{
		ft_printf("\nraw: %i\ncode: %i \npos: %i\n", validate_tokens(tokens), (validate_tokens(tokens) << 24) >> 24, validate_tokens(tokens) >> 8);
		clear_tokens(tokens, -1);
		ft_lstclear(&env, free);
		free(*line);
		return ;
	}
	i = -1;
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
	*line = NULL;
	ft_lstclear(&env, del);
	clear_tokens(tokens, -1);
	clear_3d(&split_tokens, -1, -1);
}