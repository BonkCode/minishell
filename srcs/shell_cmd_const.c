/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_const.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:48:44 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 15:22:20 by rtrant           ###   ########.fr       */
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
