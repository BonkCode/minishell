/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:08:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 17:27:22 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include <string.h>
#include "libftprintf.h"
#include "flexer.h"

static int				ft_strncmp_split(char *s1, char *s2, char c)
{
	int		i;
	char	**arr;

	i = -1;
	if (!(arr = ft_split(s2, c)))
		return (1);
	while (arr[++i])
	{
		if (!ft_strncmp(arr[i], s1, ft_strlen(arr[i]) + 1))
		{
			clear_tokens(arr, -1);
			return (0);
		}
	}
	i = -1;
	clear_tokens(arr, -1);
	return (1);
}

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
	return_command->status = code;
	if (simple_command)
	{
		free(simple_command);
		simple_command = NULL;
	}
	return (*return_command);
}

static void		get_shell_cmd(t_simple_command **simple_command,
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
			return ;
		}
	}
}

static void				get_redirect_files(char **tokens, int i,
							t_command *return_command)
{
	if (!ft_strncmp_split(tokens[i], "<", ' '))
		return_command->infile = ft_strdup(tokens[i + 1]);
	else if (!ft_strncmp(tokens[i - 1], "1", 2))
		return_command->outfile = ft_strdup(tokens[i + 1]);
	else if (!ft_strncmp(tokens[i - 1], "2", 2))
		return_command->errfile = ft_strdup(tokens[i + 1]);
	else
		return_command->outfile = ft_strdup(tokens[i + 1]);
}

static void				clear_command(t_simple_command **simple_command)
{
	if (*simple_command)
	{
		free(*simple_command);
		*simple_command = NULL;
	}
}

t_command				parse(char **tokens, t_shell_cmd cmds[7])
{
	int					i;
	int					j;
	t_command			return_command;
	t_simple_command	*list;
	t_simple_command	*s_c;

	i = -1;
	if (!(s_c = new_simple_command()))
		return (abort_parsing(&return_command, -1, s_c, &list));
	init_return_command(&return_command);
	list = NULL;
	while (tokens[++i])
	{
		if (!s_c->command)
		{
			get_shell_cmd(&s_c, tokens, i, cmds);
			if (!s_c->command)
				return (abort_parsing(&return_command, 1, s_c, &list));
		}
		else if (tokens[i][0] == '-' && !ft_strncmp(tokens[i - 1],
					s_c->command, ft_strlen(s_c->command + 1)))
		{
			if (ft_strncmp(s_c->command, "echo", 5))
				return (abort_parsing(&return_command, 2, s_c, &list));
			else if (!ft_strncmp(tokens[i], "-n", 3))
				s_c->flag = ft_strdup(tokens[i]);
			else
				ft_lstadd_back(&(s_c->arguments), ft_lstnew(tokens[i]));
		}
		else if (!ft_strncmp(tokens[i], "|", 2) ||
				!ft_strncmp(tokens[i], ";", 2))
		{
			s_c->piped = tokens[i][0] == '|' ? 1 : 0;
			ft_command_add_back(&list, s_c);
			s_c = new_simple_command();
		}
		else if (!ft_strncmp_split(tokens[i], ">> < >", ' '))
		{
			ft_command_add_back(&list, s_c);
			if (!(s_c = new_simple_command()))
				return (abort_parsing(&return_command, 3, s_c, &list));
			else if (tokens[i + 1] == 0)
				return (abort_parsing(&return_command, 4, s_c, &list));
			else
			{
				get_redirect_files(tokens, i, &return_command);
				if (tokens[i + 2] == 0)
				{
					return_command.commands = list;
					clear_command(&s_c);
					return (return_command);
				}
				i += 2;
			}
		}
		else
			ft_lstadd_back(&(s_c->arguments), ft_lstnew(ft_strdup(tokens[i])));
	}
	if (s_c->command != NULL)
		ft_command_add_back(&list, s_c);
	else if (s_c)
		clear_command(&s_c);
	return_command.commands = list;
	return (return_command);
}
