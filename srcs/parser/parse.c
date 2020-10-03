/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:08:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/02 16:21:51 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "flexer.h"

static t_simple_command	*new_simple_command(void)
{
	t_simple_command	*simple_command;

	if (!(simple_command = malloc(sizeof(t_simple_command))))
		return (NULL);
	simple_command->command = NULL;
	simple_command->flag = NULL;
	simple_command->arguments = NULL;
	simple_command->next = NULL;
	simple_command->piped = 0;
	return (simple_command);
}

void	ft_command_add_back(t_simple_command **lst, t_simple_command *new)
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

t_command		parse(char **tokens, t_shell_cmd cmds[7])
{
	int					i;
	int					j;
	t_command			return_command;
	t_simple_command	*list;
	t_simple_command	*simple_command;
	t_shell_cmd			cmd;

	i = -1;
	if (!(simple_command = new_simple_command()))
	{
		clear_command(&list);
		return_command.status = -1;
		return (return_command);
	}
	return_command.infile = NULL;
	return_command.outfile = NULL;
	return_command.errfile = NULL;
	return_command.commands = NULL;
	return_command.status = 0;
	list = NULL;
	while (tokens[++i])
	{
		if (!simple_command->command)
		{
			j = -1;
			while (++j < 7)
			{
				if (!ft_strncmp(tokens[i], cmds[j].name, ft_strlen(cmds[j].name) + 1))
				{
					cmd = cmds[j];
					simple_command->command = ft_strdup(tokens[i]);
					break ;
				}
			}
			if (!simple_command->command)
			{
				return_command.status = 1;
				return (return_command);
			}
		}
		else if (tokens[i][0] == '-' && !ft_strncmp(tokens[i - 1], cmd.name, ft_strlen(cmd.name + 1)))
		{
			if (ft_strncmp(cmd.name, "echo", 5))
			{
				clear_command(&list);
				return_command.status = 2;
				return (return_command);
			}
			else if (!ft_strncmp(tokens[i], "-n", 3))
				simple_command->flag = ft_strdup(tokens[i]);
			else
				ft_lstadd_back(&(simple_command->arguments), ft_lstnew(tokens[i]));
		}
		else if (!ft_strncmp(tokens[i], "|", 2))
		{
			simple_command->piped = 1;
			ft_command_add_back(&list, simple_command);
			simple_command = new_simple_command();
		}
		else if (!ft_strncmp(tokens[i], ";", 2))
		{
			ft_command_add_back(&list, simple_command);
			simple_command = new_simple_command();
		}
		else if (!ft_strncmp(tokens[i], ">>", 3) ||
				!ft_strncmp(tokens[i], ">", 2) ||
				!ft_strncmp(tokens[i], "<", 2))
		{
			ft_command_add_back(&list, simple_command);
			if (!(simple_command = new_simple_command()))
			{
				clear_command(&list);
				return_command.status = 2;
				return (return_command);
			}
			if (tokens[i + 1] == 0)
			{
				clear_command(&list);
				return_command.status = 3;
				return (return_command);
			}
			else
			{
				if (!ft_strncmp(tokens[i - 1], "1", 2))
					return_command.outfile = ft_strdup(tokens[i + 1]);
				if (!ft_strncmp(tokens[i - 1], "2", 2))
					return_command.errfile = ft_strdup(tokens[i + 1]);
				else
					return_command.outfile = ft_strdup(tokens[i + 1]);
				if (tokens[i + 2] == 0)
				{
					return_command.commands = list;
					return (return_command);
				}
				else
					i += 2;
			}
		}
		else
			ft_lstadd_back(&(simple_command->arguments), ft_lstnew(ft_strdup(tokens[i])));
	}
	if (simple_command->command != NULL)
		ft_command_add_back(&list, simple_command);
	return_command.commands = list;
	return (return_command);
}
