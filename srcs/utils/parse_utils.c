/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:23:22 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/31 19:27:25 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include "m_types.h"

extern t_shell_cmd	g_commands[7];

int				ft_strncmp_split(char *s1, char *s2, char c)
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

t_command		abort_parsing(t_command *return_command, int code,
				t_simple_command **simple_command, t_simple_command **list)
{
	clear_simple_commands(list);
	return_command->status = code;
	clear_simple_commands(simple_command);
	return (*return_command);
}

int				get_shell_cmd(t_simple_command **simple_command,
							char **tokens, int i, int *index)
{
	int	j;

	*index = i;
	(*simple_command)->command = ft_strdup(tokens[i]);
	j = -1;
	while (++j < 7)
	{
		if (!ft_strncmp(g_commands[j].name, (*simple_command)->command,
			ft_strlen(g_commands[j].name)))
			return (j);
	}
	return (-1);
}

void			get_redirect_files(char **tokens, int i,
							t_command *return_command)
{
	if (!ft_strncmp(tokens[i], ">>", 3))
		return_command->append = 1;
	else
		return_command->append = 0;
	if (!ft_strncmp_split(tokens[i], "<", ' '))
		ft_lstadd_back(&return_command->infile,
			ft_lstnew(ft_strdup(tokens[i + 1])));
	else if (i > 0 && !ft_strncmp(tokens[i - 1], "1", 2) ||
		i - 2 >= 0 && !ft_strncmp_split(tokens[i - 2], "< > >>", ' '))
		ft_lstadd_back(&return_command->outfile,
			ft_lstnew(ft_strdup(tokens[i + 1])));
	else if (i > 0 && !ft_strncmp(tokens[i - 1], "2", 2) ||
		i - 2 >= 0 && !ft_strncmp_split(tokens[i - 2], "< > >>", ' '))
		ft_lstadd_back(&return_command->errfile,
			ft_lstnew(ft_strdup(tokens[i + 1])));
	else if (i == 0 || !str_is_num(tokens[i - 1]) ||
		i - 2 >= 0 && !ft_strncmp_split(tokens[i - 2], "< > >>", ' '))
		ft_lstadd_back(&return_command->outfile,
			ft_lstnew(ft_strdup(tokens[i + 1])));
	else
		ft_lstadd_back(&return_command->other_files,
			ft_lstnew(ft_strdup(tokens[i + 1])));
}

void			clear_command(t_simple_command **simple_command)
{
	if (*simple_command)
	{
		free(*simple_command);
		*simple_command = NULL;
	}
}
