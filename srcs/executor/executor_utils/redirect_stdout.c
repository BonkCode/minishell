/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:18:13 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 19:45:27 by rtrant           ###   ########.fr       */
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
	while ((res = get_next_line((*fd)[1],
			(char **)&ft_lstlast(*append_buffer)->content)) > 0)
		ft_lstadd_back(append_buffer, ft_lstnew(NULL));
	close((*fd)[1]);
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

void		redirect_stdout(t_command command, int (*fd)[4])
{
	t_list	*append_buffer;

	append_buffer = NULL;
	while (command.outfile)
	{
		if (command.append &&
			(((*fd)[1] = open(command.outfile->content, O_RDONLY)) > 0))
			copy_file_content(&append_buffer, fd);
		close((*fd)[1]);
		if (((*fd)[1] = open(command.outfile->content,
							O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		{
			ft_putstr_fd("cannot open file\n", 2);
			ft_lstclear(&append_buffer, del);
			return ;
		}
		if (command.append)
			restore_file_content(&append_buffer, fd);
		if (!command.outfile->next)
			dup2((*fd)[1], 1);
		close((*fd)[1]);
		command.outfile = command.outfile->next;
	}
}
