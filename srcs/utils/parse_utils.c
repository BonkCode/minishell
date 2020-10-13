/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 16:23:22 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/13 17:26:57 by rtrant           ###   ########.fr       */
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
							char **tokens, int i)
{
	int	j;

	j = -1;
	while (++j < 7)
	{
		if (!ft_strncmp(tokens[i], g_commands[j].name,
			ft_strlen(g_commands[j].name) + 1))
		{
			(*simple_command)->command = ft_strdup(tokens[i]);
			return (0);
		}
	}
	return (1);
}

void			get_redirect_files(char **tokens, int i,
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

void			clear_command(t_simple_command **simple_command)
{
	if (*simple_command)
	{
		free(*simple_command);
		*simple_command = NULL;
	}
}
