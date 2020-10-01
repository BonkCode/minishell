/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clearer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:08:02 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/01 16:51:25 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include "libft.h"

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