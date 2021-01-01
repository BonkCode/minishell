/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:09:53 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/01 23:13:38 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
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

static void	run_command(int command_flag, t_simple_command *command,
						char **environ)
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

static void	sigint_skip(int c)
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
	t_list	*path;
	char	**split_var;
	char	**paths;

	i = -1;
	while (environ[++i])
	{
		split_var = ft_split(environ[i], '=');
		if (!ft_strncmp(split_var[0], "PATH", 5))
			break ;
		clear_tokens(split_var, -1);
		split_var = NULL;
	}
	if (!split_var)
		return (NULL);
	path = NULL;
	paths = ft_split(split_var[1], ':');
	i = -1;
	while (paths && paths[++i])
		ft_lstadd_back(&path, ft_lstnew(ft_strjoin(paths[i], "/")));
	if (paths)
		clear_tokens(paths, -1);
	clear_tokens(split_var, -1);
	return (path);
}

int			cmd_not_found(t_list **path, char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_lstclear(path, del);
	return (127);
}

void		try_rel_or_abs_path(char *command, char **args,
							char **environ, int *executed)
{
	if (ft_strchr(command, '/'))
		*executed = execve(command, args, environ);
}

int			launch_with_path_var(t_list *path, char **environ,
								char **args, t_simple_command *command)
{
	int		executed;
	char	*command_path;

	executed = 0;
	while (path)
	{
		command_path = ft_strjoin(path->content, command->command);
		if ((executed = execve(command_path,
							args, environ)) >= 0)
		{
			free(command_path);
			break ;
		}
		free(command_path);
		path = path->next;
	}
	return (executed);
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
	path = NULL;
	if (!(id = fork()))
	{
		path = get_path(environ);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		try_rel_or_abs_path(command->command, args, environ, &executed);
		if (executed < 0 &&
			launch_with_path_var(path, environ, args, command) < 0)
			exit(cmd_not_found(&path, command->command));
		ft_lstclear(&path, del);
		exit(0);
	}
	else
		wait(&g_status);
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

void		set_all_subcommands_pipe(t_command *command)
{
	t_simple_command	*first_command;

	if (command->piped)
	{
		first_command = command->commands;
		while (command->commands)
		{
			command->commands->piped = 1;
			command->commands = command->commands->next;
		}
		command->commands = first_command;
	}
}

void		init_fds(int (*fd)[4])
{
	(*fd)[0] = -1;
	(*fd)[1] = -1;
	(*fd)[2] = -1;
	(*fd)[3] = -1;
}

void		copy_std(int (*std_copy)[3])
{
	(*std_copy)[0] = dup(0);
	(*std_copy)[1] = dup(1);
	(*std_copy)[2] = dup(2);
}

void		setup_pipe(int piped, int (*pipe_fd)[2])
{
	if (piped)
	{
		pipe(*pipe_fd);
		dup2((*pipe_fd)[0], 0);
		dup2((*pipe_fd)[1], 1);
		close((*pipe_fd)[0]);
		close((*pipe_fd)[1]);
	}
}

void		restore_std_fd(int *fd, int std_fd)
{
	dup2(*fd, std_fd);
	*fd = dup(std_fd);
}

void		redirect_stdout(t_command command, int (*fd)[4])
{
	t_list	*first_line;
	t_list	*append_buffer;
	int		res;

	append_buffer = NULL;
	while (command.outfile)
	{
		if (command.append && (((*fd)[1] = open(command.outfile->content, O_RDONLY)) > 0))
		{
			ft_lstclear(&append_buffer, del);
			append_buffer = ft_lstnew(NULL);
			
			while ((res = get_next_line((*fd)[1], (char **)&ft_lstlast(append_buffer)->content)) > 0)
				ft_lstadd_back(&append_buffer, ft_lstnew(NULL));
			close((*fd)[1]);
		}
		if (!command.append && ((*fd)[1] = open(command.outfile->content, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
			return ; // todo remove leaks
		else if (command.append && ((*fd)[1] = open(command.outfile->content, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
			return ;// todo remove leaks
		if (command.append)
		{
			first_line = append_buffer;
			while (append_buffer)
			{
				if (append_buffer->content && append_buffer->next)
					ft_putendl_fd(append_buffer->content, (*fd)[1]);
				else if (append_buffer->content)
					ft_putstr_fd(append_buffer->content, (*fd)[1]);
				append_buffer = append_buffer->next;
			}
			append_buffer = first_line;
		}
		if (!command.outfile->next)
			dup2((*fd)[1], 1);
		close((*fd)[1]);
		command.outfile = command.outfile->next;
	}
}

void		redirect_stderr(t_command command, int (*fd)[4])
{
	t_list	*first_line;
	t_list	*append_buffer;

	append_buffer = NULL;
	while (command.errfile)
	{
		if (command.append && (((*fd)[2] = open(command.errfile->content, O_RDONLY)) > 0))
		{
			ft_lstclear(&append_buffer, del);
			append_buffer = ft_lstnew(NULL);
			while (get_next_line((*fd)[2], (char **)&ft_lstlast(append_buffer)->content) > 0)
			{
				ft_lstadd_back(&append_buffer, ft_lstnew(NULL));
			}
			close((*fd)[2]);
		}
		if (!command.append && ((*fd)[2] = open(command.errfile->content, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
			return ; // todo remove leaks
		else if (command.append && ((*fd)[2] = open(command.errfile->content, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
			return ;// todo remove leaks
		if (command.append)
		{
			first_line = append_buffer;
			while (append_buffer)
			{
				if (append_buffer->content && ((char *)append_buffer->content)[0])
					ft_putendl_fd(append_buffer->content, (*fd)[2]);
				append_buffer = append_buffer->next;
			}
			append_buffer = first_line;
		}
		if (!command.errfile->next)
			dup2((*fd)[2], 2);
		close((*fd)[2]);
		command.errfile = command.errfile->next;
	}
}

void		redirect_stdin(t_command command, int (*fd)[4])
{
	while (command.infile)
	{
		if (((*fd)[0] = open(command.infile->content, O_RDONLY)) < 0)
			return ; // todo
		if (!command.infile->next)
			dup2((*fd)[0], 0);
		close((*fd)[0]);
		command.infile = command.infile->next;
	}
}

void		redirect_other()
{
	
}

void		execute(char ****split_tokens, t_list *env, char **environ, int i)
{
	t_list				*first_line;
	t_list				*append_buffer;
	t_command			command;
	int					command_flag;
	t_simple_command	*s_c;
	int					std_copy[3];
	int					pipe_fd[2];
	int					fd[4];
	int					flush_flag;

	init_fds(&fd);
	append_buffer = NULL;
	init_command(&command);
	expand(&(*split_tokens)[i], env);
	glue_tokens(&(*split_tokens)[i]);
	command_flag = -1;
	get_command(&command, &command_flag, (*split_tokens)[i]);
	set_all_subcommands_pipe(&command);
	s_c = command.commands;
	copy_std(&std_copy);
	flush_flag = 0;
	setup_pipe(command.piped, &pipe_fd);
	while (command.commands)
	{
		get_shell_command_index(&command_flag, command.commands->command);
		if (command.piped && !command.commands->next)
			restore_std_fd(std_copy + 1, 1);
		if (!command.commands->next)
		{
			redirect_stdout(command, &fd);
			redirect_stderr(command, &fd);
			redirect_stdin(command, &fd);
			while (command.other_files)
			{
				if (!command.append && (fd[4] = open(command.other_files->content, O_RDONLY)) > 0)
					return ; // todo
				else if ((fd[4] = open(command.other_files->content, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
					return ; // todo
				close(fd[4]);
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
	ft_lstclear(&append_buffer, del);
	dup2(std_copy[0], 0);
	close(std_copy[0]);
	dup2(std_copy[1], 1);
	close(std_copy[1]);
	dup2(std_copy[2], 2);
	close(std_copy[2]);
	command.commands = s_c;
	free_command(&command);
}

int			return_token_alloc_error(char **line, t_list **env)
{
	if ((*line)[0])
		ft_putstr_fd("minishell: failed to create tokens from input\n", 2);
	ft_lstclear(env, del);
	free(*line);
	return (-1);
}

int			return_syntax_error(int status, t_list **env,
								char **line, char **tokens)
{
	ft_putstr_fd("minishell: sntax error near unexpected token '", 2);
	ft_putstr_fd(tokens[status >> 8], 2);
	ft_putstr_fd("'\n", 2);
	clear_tokens(tokens, -1);
	ft_lstclear(env, del);
	free(*line);
	return (status & 0xff00);
}

int			return_split_tokens_err(t_list **env, char **tokens, char **line)
{
	clear_tokens(tokens, -1);
	ft_lstclear(env, del);
	free(*line);
	return (-2);
}

int			return_normal(t_list **env, char **line, char ****split_tokens,
						char **tokens)
{
	free(*line);
	*line = NULL;
	ft_lstclear(env, del);
	clear_tokens(tokens, -1);
	clear_3d(split_tokens, -1, -1);
	return (0);
}

void		init_vars(t_list **env, char ***tokens, char ****split_tokens)
{
	*tokens = NULL;
	*split_tokens = NULL;
	*env = NULL;
}

int			handle_line(char **line, char **environ)
{
	pid_t				id;
	t_list				*env;
	char				**tokens;
	char				***split_tokens;
	int					i;

	init_vars(&env, &tokens, &split_tokens);
	ft_get_env(&env, environ);
	tokens = tokenize(*line);
	if (!tokens)
		return (return_token_alloc_error(line, &env));
	if (i = validate_tokens(tokens))
		return (return_syntax_error(i, &env, line, tokens));
	i = -1;
	if (!(split_tokens = split_tokens_by_semicolons(tokens)))
		return (return_split_tokens_err(&env, tokens, line));
	i = -1;
	while (split_tokens[++i])
		execute(&split_tokens, env, environ, i);
	return (return_normal(&env, line, &split_tokens, tokens));
}
