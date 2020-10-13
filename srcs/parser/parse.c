/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:08:25 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/13 18:17:13 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include <string.h>
#include "libftprintf.h"
#include "flexer.h"

extern t_shell_cmd	g_commands[7];

void					try_sep(char **tokens, int i, t_simple_command **s_c,
								t_simple_command **list)
{
	(*s_c)->piped = tokens[i][0] == '|' ? 1 : 0;
	ft_command_add_back(list, (*s_c));
	(*s_c) = new_simple_command();
}

int						is_flag(char **tokens, int i, t_simple_command **s_c)
{
	if (tokens[i][0] == '-' && !ft_strncmp(tokens[i - 1],
					(*s_c)->command, ft_strlen((*s_c)->command + 1)))
		return (1);
	return (0);
}

int						sep_or_add(t_tokens tokens_pos, t_simple_command **list,
							t_simple_command **s_c, t_command *return_command)
{
	int		i;
	char	**tokens;

	tokens = tokens_pos.tokens;
	i = tokens_pos.i;
	if (!ft_strncmp_split(tokens[i], ">> < >", ' '))
	{
		ft_command_add_back(list, (*s_c));
		if (!((*s_c) = new_simple_command()) || tokens[i + 1] == 0)
			return (3);
		get_redirect_files(tokens, i, return_command);
		if (tokens[i += 2] == 0)
			return (-1);
	}
	else
		ft_lstadd_back(&((*s_c)->args), ft_lstnew(ft_strdup(tokens[i])));
	return (0);
}

t_command				parse_tokens(char **t, t_simple_command **list,
							t_simple_command **s_c, t_command *return_command)
{
	int	i;

	i = -1;
	while (t[++i])
	{
		if (!(*s_c)->command && get_shell_cmd(s_c, t, i) != 0)
			return (abort_parsing(return_command, 1, s_c, list));
		else if (is_flag(t, i, s_c))
		{
			if (ft_strncmp((*s_c)->command, "echo", 5))
				return (abort_parsing(return_command, 2, s_c, list));
			else if (!ft_strncmp(t[i], "-n", 3))
				(*s_c)->flag = ft_strdup(t[i]);
			else
				ft_lstadd_back(&((*s_c)->args), ft_lstnew(ft_strdup(t[i])));
		}
		else if (!ft_strncmp_split(t[i], "|", ' '))
			try_sep(t, i, s_c, list);
		else if (sep_or_add(new_t_token(t, i), list, s_c,
				return_command) > 0 && (i += 2))
			return (abort_parsing(return_command, 3, s_c, list));
		else if (t[i] == 0)
			break ;
	}
	return (*return_command);
}

t_command				parse(char **tokens)
{
	t_command			return_command;
	t_simple_command	*list;
	t_simple_command	*s_c;

	if (!(s_c = new_simple_command()))
		return (abort_parsing(&return_command, -1, &s_c, &list));
	init_return_command(&return_command);
	list = NULL;
	parse_tokens(tokens, &list, &s_c, &return_command);
	if (return_command.status != 0)
		return (return_command);
	if (s_c->command != NULL)
		ft_command_add_back(&list, s_c);
	else if (s_c)
		clear_simple_commands(&s_c);
	return_command.commands = list;
	return (return_command);
}
