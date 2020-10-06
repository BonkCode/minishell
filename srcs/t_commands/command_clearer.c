/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clearer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:08:02 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/03 17:05:41 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

static	void	del(void *data)
{
	if (data)
		free(data);
	data = NULL;
}

t_simple_command	*clear_command(t_simple_command **command)
{
	if (!(*command))
		return (NULL);
	if ((*command)->flag)
	{
		free((*command)->flag);
		(*command)->flag = NULL;
	}
	if ((*command)->arguments)
	{
		ft_putstr_fd("qqq\n", 1);
		ft_lstclear(&(*command)->arguments, &del);
		(*command)->arguments = NULL;
	}
	if ((*command)->command)
	{
		free((*command)->command);
		(*command)->command = NULL;
	}
	(*command)->next = clear_command(&(*command)->next);
	free(*command);
	return (*command = NULL);
}
