/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_dummy_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/26 23:01:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

int	dummy_echo(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}

int	dummy_cd(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}

int	dummy_export(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}
