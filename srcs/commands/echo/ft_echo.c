/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:26:29 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/29 14:14:25 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

int		ft_echo(t_command command)
{
	int i;
	int n;

	n = 0;
	i = 0;
	if(ft_strcmp(command.command->flags, "-n") == 0)
		n = 1;
	if (!command.command->arguments[0])
	{
		if (!n)
			ft_putstr_fd("\n", 1);
		return (0);
	}
	while (command.command->arguments[i])
	{
		ft_putstr_fd(command.command->arguments[i], 1);
		command.command->arguments[i + 1] ? ft_putstr_fd(" ", 1) : 0;
		++i;
	}
	!n ? ft_putstr_fd("\n", 1) : 0;
	return (0);
}
