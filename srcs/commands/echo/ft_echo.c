/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 17:36:11 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/26 17:38:21 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../../headers/m_types.h"

int	ft_echo(t_command command)
{
	ft_putstr_fd(command.arguments[0]);
	return (0)
}
