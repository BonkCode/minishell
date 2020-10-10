/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:20:56 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/08 16:25:36 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include "m_types.h"

t_simple_command		*new_simple_command(void)
{
	t_simple_command	*simple_command;

	if (!(simple_command = malloc(sizeof(t_simple_command))))
		return (NULL);
	simple_command->command = NULL;
	simple_command->flag = NULL;
	simple_command->args = NULL;
	simple_command->next = NULL;
	simple_command->piped = 0;
	return (simple_command);
}

void					ft_command_add_back(t_simple_command **lst,
											t_simple_command *new)
{
	t_simple_command *cache;

	cache = *lst;
	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (cache->next)
				cache = cache->next;
			cache->next = new;
		}
	}
}

void					init_return_command(t_command *return_command)
{
	return_command->infile = NULL;
	return_command->outfile = NULL;
	return_command->errfile = NULL;
	return_command->commands = NULL;
	return_command->status = 0;
}

t_tokens				new_t_token(char **tokens, int i)
{
	t_tokens	new;

	new.tokens = tokens;
	new.i = i;
	return (new);
}
