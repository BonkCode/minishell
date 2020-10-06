/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:54 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 15:24:28 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

void	dummy_unset(t_command command)
{
	ft_strlen(command.commands->command);
}

void	dummy_env(t_command command)
{
	ft_strlen(command.commands->command);
}

void	dummy_exit(t_command command)
{
	ft_strlen(command.commands->command);
}
