/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/12 01:15:55 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

void	dummy_echo(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}

void	dummy_cd(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}

void	dummy_export(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}
