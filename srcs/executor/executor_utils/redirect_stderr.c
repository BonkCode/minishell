/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stderr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:22:44 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 20:36:45 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "m_types.h"
#include <fcntl.h>
#include "flexer.h"

static void	copy_file_content(t_list **append_buffer, int (*fd)[4])
{
	int	res;

	ft_lstclear(append_buffer, del);
	*append_buffer = ft_lstnew(NULL);
	while ((res = get_next_line((*fd)[2],
			(char **)&ft_lstlast(*append_buffer)->content)) > 0)
		ft_lstadd_back(append_buffer, ft_lstnew(NULL));
	close((*fd)[2]);
}

static void	restore_file_content(t_list **append_buffer, int (*fd)[4])
{
	t_list	*first_line;

	first_line = (*append_buffer);
	while ((*append_buffer))
	{
		if ((*append_buffer)->content && (*append_buffer)->next)
			ft_putendl_fd((*append_buffer)->content, (*fd)[1]);
		else if ((*append_buffer)->content)
			ft_putstr_fd((*append_buffer)->content, (*fd)[1]);
		(*append_buffer) = (*append_buffer)->next;
	}
	(*append_buffer) = first_line;
	ft_lstclear(append_buffer, del);
}

void		redirect_stderr(t_command command, int (*fd)[4])
{
	t_list	*append_buffer;

	append_buffer = NULL;
	while (command.errfile)
	{
		if (command.append &&
			(((*fd)[2] = open(command.errfile->content, O_RDONLY)) > 0))
			copy_file_content(&append_buffer, fd);
		close((*fd)[2]);
		if (((*fd)[2] = open(command.errfile->content,
							O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		{
			ft_putstr_fd("cannot open file\n", 2);
			ft_lstclear(&append_buffer, del);
			return ;
		}
		if (command.append)
			restore_file_content(&append_buffer, fd);
		if (!command.errfile->next)
			dup2((*fd)[2], 2);
		close((*fd)[2]);
		command.errfile = command.errfile->next;
	}
}
