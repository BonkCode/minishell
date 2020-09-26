/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_const.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:48:44 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/26 16:06:36 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

t_shell_cmd	new_shell_cmd(char *name, int (*func)(t_command command))
{
	t_shell_cmd	new_cmd;

	new_cmd.name = name;
	new_cmd.function = func;
	return (new_cmd);
}