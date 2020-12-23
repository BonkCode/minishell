/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_const.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:48:44 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/23 21:27:10 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

t_shell_cmd	new_shell_cmd(char *name, void (*func)(t_simple_command command))
{
	t_shell_cmd	new_cmd;

	new_cmd.name = name;
	new_cmd.function = func;
	return (new_cmd);
}
