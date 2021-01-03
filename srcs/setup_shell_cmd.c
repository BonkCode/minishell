/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:07 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 20:00:17 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include "m_types.h"
#include "commands.h"

void		setup_commands(t_shell_cmd commands[7])
{
	(commands)[0] = new_shell_cmd("echo", &ft_echo);
	(commands)[1] = new_shell_cmd("cd", &ft_cd);
	(commands)[2] = new_shell_cmd("export", &ft_export);
	(commands)[3] = new_shell_cmd("unset", &ft_unset);
	(commands)[4] = new_shell_cmd("env", &ft_env);
	(commands)[5] = new_shell_cmd("exit", &ft_exit);
	(commands)[6] = new_shell_cmd("pwd", &ft_pwd);
}
