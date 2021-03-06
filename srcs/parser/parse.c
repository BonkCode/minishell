/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:08:25 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/16 18:21:20 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include <stdlib.h>
#include <string.h>
#include "libftprintf.h"
#include "flexer.h"

extern t_shell_cmd	g_commands[7];

static int				try_sep(t_command *command, t_simple_command **s_c,
								t_simple_command **list)
{
	command->piped = 1;
	(*s_c)->piped = 1;
	ft_command_add_back(list, (*s_c));
	(*s_c) = new_simple_command();
	return (1);
}

static int				sep_or_add(t_tokens tokens_pos,
							t_simple_command **s_c, t_command *return_command)
{
	int		*i;
	char	**tokens;

	tokens = tokens_pos.tokens;
	i = tokens_pos.i;
	if (!ft_strncmp_split(tokens[*i], ">> < >", ' '))
	{
		get_redirect_files(tokens, *i, return_command);
		*i += 1;
	}
	else if (ft_strncmp_split(tokens[*i + 1], "< > >>", ' ') ||
							!str_is_num(tokens[*i]))
		ft_lstadd_back(&((*s_c)->args), ft_lstnew(ft_strdup(tokens[*i])));
	return (0);
}

t_command				parse_tokens(char **t, t_simple_command **list,
							t_simple_command **s_c, t_command *return_command)
{
	int	i;
	int	c_index;

	i = -1;
	while (t[++i])
	{
		if (!(*s_c)->command && ft_strncmp_split(t[i], "< > >>", ' ') &&
			!(str_is_num(t[i]) && !ft_strncmp_split(t[i + 1], "< > >>", ' ')))
			get_shell_cmd(s_c, t, i, &c_index);
		if (is_flag(t, i, c_index))
		{
			if (!ft_strncmp(t[i], "-n", 3) && prev_is_flag(t, i, c_index) &&
						!ft_strncmp((*s_c)->command, "echo", 5))
				set_flag(s_c, t, i);
			else
				ft_lstadd_back(&((*s_c)->args), ft_lstnew(ft_strdup(t[i])));
		}
		else if (!ft_strncmp(t[i], "|", 2))
			try_sep(return_command, s_c, list);
		else if (sep_or_add(new_t_token(t, &i), s_c, return_command) > 0)
			return (abort_parsing(return_command, 3, s_c, list));
		if (!t[i] || t[i][0] == '\0')
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
	if (s_c)
	{
		if (s_c->command != NULL)
			ft_command_add_back(&list, s_c);
		else
			clear_simple_commands(&s_c);
	}
	return_command.commands = list;
	return (return_command);
}
