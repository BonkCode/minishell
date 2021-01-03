/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:46:32 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 20:04:00 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"

static void	flush_pipe(int fd)
{
	char	buf[5];
	int		chars_read;

	chars_read = read(fd, buf, 5);
	while (chars_read == 5)
		chars_read = read(fd, buf, 5);
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

void		redirect_pipes(int flush_flag, t_command command, t_pipe *pipe_fd)
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
}

void		flush_pipes(int flush_flag, t_command command, t_pipe *pipe_fd)
{
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
}

void		close_pipe(t_pipe *pipe_fd)
{
	close(pipe_fd->fd_1[0]);
	close(pipe_fd->fd_1[1]);
	close(pipe_fd->fd_2[0]);
	close(pipe_fd->fd_2[1]);
}
