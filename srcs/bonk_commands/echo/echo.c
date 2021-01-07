/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:08:20 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 20:37:40 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"

extern int	g_status;

int	ft_echo(t_simple_command command, char **environ)
{
	command.args = command.args->next;
	while (command.args)
	{
		ft_putstr_fd(command.args->content, 1);
		ft_putchar_fd(' ', 1);
		command.args = command.args->next;
	}
	if (!command.flag)
		ft_putstr_fd("\n", 1);
	return (0);
	environ = environ;
}
