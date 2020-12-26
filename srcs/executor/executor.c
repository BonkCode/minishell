/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:09:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/27 02:26:19 by rtrant           ###   ########.fr       */
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

static void	run_command(int command_flag, t_simple_command *command, char **environ)
{
	g_status = g_commands[command_flag].function(*command, environ);
	g_status = g_status << 8;
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
		clear_tokens(split_var, -1);
		env = env->next;
	}
	path = NULL;
	if (!ft_strncmp(split_var[0], "PATH", 5))
		paths = ft_split(split_var[1], ':');
	i = -1;
	while (paths && paths[++i] && !ft_strncmp(split_var[0], "PATH", 5))
		ft_lstadd_back(&path, ft_lstnew(ft_strjoin(paths[i], "/")));
	if (!ft_strncmp(split_var[0], "PATH", 5) && paths)
		clear_tokens(paths, -1);
	clear_tokens(split_var, -1);
	ft_lstclear(&env, del);
	return (path);
}

static void	run_executable(t_simple_command *command, char **environ)
{
	pid_t	id;
	char	**args;
	t_list	*path;
	int		executed;

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
		if (ft_strchr(command->command, '/'))
			executed = execve(command->command, args, environ);
		while (path && executed < 0)
		{
			if ((executed = execve(ft_strjoin(path->content, command->command), args, environ)) >= 0)
				break ;
			path = path->next;
		}
		if (executed < 0)
		{
			ft_putstr_fd(command->command, 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_lstclear(&path, del);
			exit(127);
		}
		ft_lstclear(&path, del);
		exit(0);
	}
	else
	{
		wait(&g_status);
	}
	signal(SIGINT, sigint_handler);
}

void		flush_pipe(int fd)
{
	char	buf[5];
	int		chars_read;
	
	chars_read = read(fd, buf, 5);
	while (chars_read == 5)
		chars_read = read(fd, buf, 5);
}

void		get_shell_command_index(int *command_flag, char *command)
{
	int	i;

	i = -1;
	*command_flag = -1;
	while (++i < 7)
	{
		if (ft_strncmp(command, g_commands[i].name,
				ft_strlen(g_commands[i].name) + 1) == 0)
		{
			*command_flag = i;
			return ;
		}
	}
}

void		execute(char ****split_tokens, t_list *env, char **environ, int i)
{
	t_command			command;
	int					command_flag;
	t_simple_command	*s_c;
	int					std_copy[3];
	int					pipe_fd[2];
	int					fd[4];
	int					flush_flag;
	t_simple_command	*first_command;
	
	fd[0] = -1;
	fd[1] = -1;
	fd[2] = -1;
	fd[3] = -1;
	init_command(&command);
	expand(&(*split_tokens)[i], env);
	//print_2d((*split_tokens)[i]);
	glue_tokens(&(*split_tokens)[i]);
//	print_2d((*split_tokens)[i]);
	//ft_putchar_fd('\n', 1);
	command_flag = -1;
	//print_2d((*split_tokens)[i]);
	get_command(&command, &command_flag, (*split_tokens)[i]);
	if (command.piped)
	{
		first_command = command.commands;
		while (command.commands)
		{
			command.commands->piped = 1;
			command.commands = command.commands->next;
		}
		command.commands = first_command;
	}
	s_c = command.commands;
	//print_commands(command);
	//ft_putstr_fd("\n\n", 1);
	std_copy[0] = dup(0);
	std_copy[1] = dup(1);
	std_copy[2] = dup(2);
	flush_flag = 0;
	if (command.piped)
	{
		pipe(pipe_fd);
		dup2(pipe_fd[0], 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	while (command.commands)
	{
		get_shell_command_index(&command_flag, command.commands->command);
		if (command.piped && !command.commands->next)
		{
			dup2(std_copy[1], 1);
			std_copy[1] = dup(1);
		}
		else if (!command.commands->next)
		{
			while (command.outfile)
			{
				if (!command.append && (fd[1] = open(command.outfile->content, O_RDONLY)) > 0)
					return ; // todo remove leaks
				else if ((fd[1] = open(command.outfile->content, O_WRONLY | O_CREAT)) < 0)
					return ; // todo remove leaks
				if (!command.outfile->next)
					dup2(fd[1], 1);
				close(fd[1]);
				command.outfile = command.outfile->next;
			}
			while (command.errfile)
			{
				if (!command.append && (fd[2] = open(command.errfile->content, O_RDONLY)) > 0)
					return ; // todo
				else if ((fd[2] = open(command.errfile->content, O_WRONLY | O_CREAT)) < 0)
					return ; // todo
				if (!command.errfile->next)
					dup2(fd[2], 2);
				close(fd[2]);
				command.errfile = command.errfile->next;
			}
			while (command.infile)
			{
				if ((fd[0] = open(command.infile->content, O_RDONLY)) < 0)
					return ; // todo
				if (!command.infile->next)
					dup2(fd[0], 0);
				close(fd[0]);
				command.infile = command.infile->next;
			}
			while (command.other_files)
			{
				if (!command.append && (fd[4] = open(command.other_files->content, O_RDONLY)) > 0)
					return ; // todo
				else if ((fd[4] = open(command.other_files->content, O_WRONLY | O_CREAT)) < 0)
					return ; // todo
				close (fd[4]);
				command.other_files = command.other_files->next;
			}
		}
		if (command_flag < 0)
			run_executable(command.commands, environ);
		else
			run_command(command_flag, command.commands, environ);
		g_status = (g_status & 0xff00) >> 8;
		command.commands = command.commands->next;
		if (flush_flag == 1)
		{
			flush_flag = 0;
			flush_pipe(0);
		}
		else
			flush_flag = 1;
	}
	dup2(std_copy[0], 0);
	close(std_copy[0]);
	dup2(std_copy[1], 1);
	close(std_copy[1]);
	dup2(std_copy[2], 2);
	close(std_copy[2]);
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