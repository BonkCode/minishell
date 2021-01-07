/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:21:09 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 20:35:15 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

int		ft_env(t_simple_command command, char **environ)
{
	int		i;

	i = -1;
	while (environ[++i])
		ft_putendl_fd(environ[i], 1);
	return (0);
	command = command;
}
