/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:54 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/12 01:15:50 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

void	dummy_unset(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}

void	dummy_env(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}

void	dummy_exit(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}

void	dummy_pwd(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit (0);
}
