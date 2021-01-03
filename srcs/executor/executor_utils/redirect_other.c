/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:49:56 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:50:43 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include <fcntl.h>

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
