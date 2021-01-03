/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:36:08 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:43:43 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"

extern int			g_status;
extern t_shell_cmd	g_commands[7];

void			run_command(int command_flag, t_simple_command *command,
						char **environ)
{
	g_status = g_commands[command_flag].function(*command, environ);
	g_status = g_status << 8;
}
