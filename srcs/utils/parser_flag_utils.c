/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flag_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:21:34 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/16 18:22:16 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "flexer.h"

int					prev_is_flag(char **tokens, int i, int command_index)
{
	if (i == 0 || i == command_index)
		return (1);
	if (ft_strncmp(tokens[i], "-n", 3))
		return (0);
	return (prev_is_flag(tokens, i - 1, command_index));
}

int					is_flag(char **tokens, int i, int command_index)
{
	if (tokens[i][0] == '-' || prev_is_flag(tokens, i, command_index))
		return (1);
	return (0);
}

void				set_flag(t_simple_command **s_c, char **tokens, int i)
{
	if ((*s_c)->flag)
	{
		free((*s_c)->flag);
		(*s_c)->flag = NULL;
	}
	(*s_c)->flag = ft_strdup(tokens[i]);
}
