/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:08:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/01 17:34:10 by rtrant           ###   ########.fr       */
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
	/*
	if (!(return_command.infile = ft_strdup("")))
	{
		clear_command(&list);
		return_command.status = -2;
		return (return_command);
	}
	if (!(return_command.errfile = ft_strdup("")))
	{
		clear_command(&list);
		return_command.status = -3;
		return (return_command);
	}
	if (!(return_command.outfile = ft_strdup("")))
	{
		clear_command(&list);
		return_command.status = -4;
		return (return_command);
	}
	*/
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
					ft_putstr_fd(tokens[i], 1);
					simple_command->command = strdup(tokens[i]);
					break ;
				}
			}
			if (!simple_command->command)
			{
				return_command.status = 1;
				return (return_command);
			}
		}
		/*
		else if (tokens[i][0] == '-')
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
					return_command.outfile = tokens[i + 1];
				if (!ft_strncmp(tokens[i - 1], "2", 2))
					return_command.errfile = tokens[i + 1];
				else
					return_command.outfile = tokens[i + 1];
			}
			break ;
		}
		*/
		else
			ft_lstadd_back(&(simple_command->arguments), ft_lstnew(tokens[i]));
		ft_command_add_back(&list, simple_command);
		simple_command = new_simple_command();
	}
	return_command.commands = list;
	return (return_command);
}
