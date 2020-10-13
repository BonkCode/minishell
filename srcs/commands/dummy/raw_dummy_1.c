/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_dummy_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/13 17:06:04 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

void	dummy_echo(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}

void	dummy_cd(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}

void	dummy_export(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}
