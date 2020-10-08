/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clearer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:08:02 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/08 15:18:47 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

static	void		del(void *data)
{
	if (data)
		free(data);
	data = NULL;
}

t_simple_command	*clear_simple_commands(t_simple_command **command)
{
	if (!(*command))
		return (NULL);
	if ((*command)->flag)
	{
		free((*command)->flag);
		(*command)->flag = NULL;
	}
	if ((*command)->args)
	{
		ft_lstclear(&(*command)->args, &del);
		(*command)->args = NULL;
	}
	if ((*command)->command)
	{
		free((*command)->command);
		(*command)->command = NULL;
	}
	(*command)->next = clear_simple_commands(&(*command)->next);
	free(*command);
	return (*command = NULL);
}

void				free_command(t_command *command)
{
	clear_simple_commands(&command->commands);
	if (command->infile)
	{
		free(command->infile);
		command->infile = NULL;
	}
	if (command->outfile)
	{
		free(command->outfile);
		command->outfile = NULL;
	}
	if (command->errfile)
	{
		free(command->errfile);
		command->errfile = NULL;
	}
}
