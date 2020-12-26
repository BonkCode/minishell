/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_const.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:48:44 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/26 22:56:25 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

t_shell_cmd	new_shell_cmd(char *name, int (*func)(t_simple_command command, char **environ))
{
	t_shell_cmd	new_cmd;

	new_cmd.name = name;
	new_cmd.function = func;
	return (new_cmd);
}
