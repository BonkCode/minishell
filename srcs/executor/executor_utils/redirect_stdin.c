/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:50:01 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:50:24 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include <fcntl.h>

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
