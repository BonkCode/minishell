/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:09:53 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:39:51 by rtrant           ###   ########.fr       */
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

void		redirect_stdin(t_command command, int (*fd)[4])
{
	while (command.infile)
	{
		if (((*fd)[0] = open(command.infile->content, O_RDONLY)) < 0)
			return ;
		if (!command.infile->next)
			dup2((*fd)[0], 0);
		close((*fd)[0]);
		command.infile = command.infile->next;
	}
}

void		redirect_other(t_command command, int (*fd)[4])
{
	while (command.other_files)
	{
		if (!command.append &&
			((*fd)[3] = open(command.other_files->content, O_RDONLY)) > 0)
			return ;
		else if (((*fd)[3] = open(
			command.other_files->content, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
			return ;
		close((*fd)[3]);
		command.other_files = command.other_files->next;
	}
}

void		redirect_all(t_command command, int (*fd)[4])
{
	redirect_stdout(command, fd);
	redirect_stderr(command, fd);
	redirect_stdin(command, fd);
	redirect_other(command, fd);
}

void		execute_commands(t_command command, int (*std_copy)[3],
						t_pipe *pipe_fd, char **environ)
{
	int	fd[4];
	int	flush_flag;
	int	command_flag;

	init_fds(&fd);
	pipe(pipe_fd->fd_1);
	pipe(pipe_fd->fd_2);
	flush_flag = 1;
	while (command.commands)
	{
		if (flush_flag % 2 == 0 && command.piped)
		{
			dup2(pipe_fd->fd_1[READ_END], READ_END);
			dup2(pipe_fd->fd_2[WRITE_END], WRITE_END);
			close(pipe_fd->fd_1[WRITE_END]);
		}
		else if (command.piped)
		{
			dup2(pipe_fd->fd_1[WRITE_END], WRITE_END);
			dup2(pipe_fd->fd_2[READ_END], READ_END);
			close(pipe_fd->fd_2[WRITE_END]);
		}
		get_shell_command_index(&command_flag, command.commands->command);
		if (command.piped && !command.commands->next)
			restore_std_fd(*std_copy + 1, 1);
		if (!command.commands->next)
			redirect_all(command, &fd);
		if (command_flag < 0)
			run_executable(command.commands, environ);
		else
			run_command(command_flag, command.commands, environ);
		g_status = (g_status & 0xff00) >> 8;
		command.commands = command.commands->next;
		if (flush_flag % 2 == 0 && command.piped)
		{
			flush_pipe(pipe_fd->fd_1[READ_END]);
			close(pipe_fd->fd_1[READ_END]);
			pipe(pipe_fd->fd_1);
		}
		else if (command.piped)
		{
			flush_pipe(pipe_fd->fd_2[READ_END]);
			close(pipe_fd->fd_2[READ_END]);
			pipe(pipe_fd->fd_2);
		}
		++flush_flag;
	}
	close(pipe_fd->fd_1[0]);
	close(pipe_fd->fd_1[1]);
	close(pipe_fd->fd_2[0]);
	close(pipe_fd->fd_2[1]);
}

void		execute(char ****split_tokens, t_list *env, char **environ, int i)
{
	t_command			command;
	int					command_flag;
	int					std_copy[3];
	t_pipe				pipe_fd;

	init_command(&command);
	expand(&(*split_tokens)[i], env);
	glue_tokens(&(*split_tokens)[i]);
	command_flag = -1;
	get_command(&command, &command_flag, (*split_tokens)[i]);
	set_all_subcommands_pipe(&command);
	copy_std(&std_copy);
	//setup_pipe(command.piped, &pipe_fd, -1);
	execute_commands(command, &std_copy, &pipe_fd, environ);
	restore_std(&std_copy);
	free_command(&command);
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
