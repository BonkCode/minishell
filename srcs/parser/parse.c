/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:08:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 16:26:40 by rtrant           ###   ########.fr       */
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

static void				init_return_command(t_command *return_command)
{
	return_command->infile = NULL;
	return_command->outfile = NULL;
	return_command->errfile = NULL;
	return_command->commands = NULL;
	return_command->status = 0;
}

static t_command		abort_parsing(t_command *return_command, int code,
				t_simple_command *simple_command, t_simple_command **list)
{
	clear_simple_commands(list);
	return_command->status = -1;
	if (simple_command)
	{
		free(simple_command);
		simple_command = NULL;
	}
	return (*return_command);
}

static t_shell_cmd		get_shell_cmd(t_simple_command **simple_command,
							char **tokens, int i, t_shell_cmd cmds[7])
{
	int	j;

	j = -1;
	while (++j < 7)
	{
		if (!ft_strncmp(tokens[i], cmds[j].name,
			ft_strlen(cmds[j].name) + 1))
		{
			(*simple_command)->command = ft_strdup(tokens[i]);
			return (cmds[j]);
		}
	}
	return (cmds[j]);
}

static void				get_redirect_files(char **tokens, int i,
							t_command *return_command)
{
	if (!ft_strncmp(tokens[i - 1], "1", 2))
		return_command->outfile = ft_strdup(tokens[i + 1]);
	if (!ft_strncmp(tokens[i - 1], "2", 2))
		return_command->errfile = ft_strdup(tokens[i + 1]);
	else
		return_command->outfile = ft_strdup(tokens[i + 1]);
}

t_command				parse(char **tokens, t_shell_cmd cmds[7])
{
	int					i;
	int					j;
	t_command			return_command;
	t_simple_command	*list;
	t_simple_command	*simple_command;
	t_shell_cmd			cmd;

	i = -1;
	if (!(simple_command = new_simple_command()))
		return (abort_parsing(&return_command, -1, simple_command, &list));
	init_return_command(&return_command);
	list = NULL;
	while (tokens[++i])
	{
		if (!simple_command->command)
		{
			cmd = get_shell_cmd(&simple_command, tokens, i, cmds);
			if (!simple_command->command)
				return (abort_parsing(&return_command, 1,
							simple_command, &list));
		}
		else if (tokens[i][0] == '-' && !ft_strncmp(tokens[i - 1],
					cmd.name, ft_strlen(cmd.name + 1)))
		{
			if (ft_strncmp(cmd.name, "echo", 5))
				return (abort_parsing(&return_command, 2,
									simple_command, &list));
			else if (!ft_strncmp(tokens[i], "-n", 3))
				simple_command->flag = ft_strdup(tokens[i]);
			else
				ft_lstadd_back(&(simple_command->arguments),
								ft_lstnew(tokens[i]));
		}
		else if (!ft_strncmp(tokens[i], "|", 2) ||
				!ft_strncmp(tokens[i], ";", 2))
		{
			simple_command->piped = tokens[i][0] == '|' ? 1 : 0;
			ft_command_add_back(&list, simple_command);
			simple_command = new_simple_command();
		}
		else if (!ft_strncmp(tokens[i], ">>", 3) ||
				!ft_strncmp(tokens[i], ">", 2) ||
				!ft_strncmp(tokens[i], "<", 2))
		{
			ft_command_add_back(&list, simple_command);
			if (!(simple_command = new_simple_command()))
				return (abort_parsing(&return_command, 3,
						simple_command, &list));
			else if (tokens[i + 1] == 0)
				return (abort_parsing(&return_command, 4,
									simple_command, &list));
			else
			{
				get_redirect_files(tokens, i, &return_command);
				if (tokens[i + 2] == 0)
				{
					return_command.commands = list;
					if (simple_command)
					{
						free(simple_command);
						simple_command = NULL;
					}
					return (return_command);
				}
				i += 2;
			}
		}
		else
			ft_lstadd_back(&(simple_command->arguments),
						ft_lstnew(ft_strdup(tokens[i])));
	}
	if (simple_command->command != NULL)
		ft_command_add_back(&list, simple_command);
	else if (simple_command)
	{
		free(simple_command);
		simple_command = NULL;
	}
	return_command.commands = list;
	return (return_command);
}
