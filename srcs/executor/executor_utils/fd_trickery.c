/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_trickery.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:28:42 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:13:07 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		restore_std(int (*std_copy)[3])
{
	dup2((*std_copy)[0], 0);
	close((*std_copy)[0]);
	dup2((*std_copy)[1], 1);
	close((*std_copy)[1]);
	dup2((*std_copy)[2], 2);
	close((*std_copy)[2]);
}

void		restore_std_fd(int *fd, int std_fd)
{
	dup2(*fd, std_fd);
	*fd = dup(std_fd);
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

void		setup_pipe(int piped, int (*pipe_fd)[2], int fd)
{
	if (piped && fd < 0)
	{
		pipe(*pipe_fd);
		dup2((*pipe_fd)[0], 0);
		dup2((*pipe_fd)[1], 1);
		close((*pipe_fd)[0]);
		close((*pipe_fd)[1]);
	}
	else if (piped)
	{
		pipe(*pipe_fd);
		dup2((*pipe_fd)[0], fd);
		close((*pipe_fd)[0]);
		close((*pipe_fd)[1]);
	}
}
