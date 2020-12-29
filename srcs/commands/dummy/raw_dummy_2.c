/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_dummy_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:54 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/26 23:01:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

int	dummy_unset(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}

int	dummy_env(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}

int	dummy_exit(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}

int	dummy_pwd(t_command command, char **environ)
{
	ft_putendl_fd(command.commands->command, 1);
	return(0);
}
