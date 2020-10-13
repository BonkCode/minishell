/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_dummy_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:54 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/13 17:17:33 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

void	dummy_unset(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}

void	dummy_env(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}

void	dummy_exit(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}

void	dummy_pwd(t_command command)
{
	ft_putendl_fd(command.commands->command, 1);
	exit(0);
}
