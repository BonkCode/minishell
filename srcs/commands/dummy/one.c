/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:28:53 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 14:30:34 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"

void	dummy_echo(t_command command)
{
	ft_strlen(command.commands->command);
}

void	dummy_cd(t_command command)
{
	ft_strlen(command.commands->command);
}

void	dummy_export(t_command command)
{
	ft_strlen(command.commands->command);
}
