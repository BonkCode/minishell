/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:25:03 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/08 17:25:05 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_echo(t_command command)
{
	int i;
	int n;

	n = 0;
	i = 0;
	if(ft_strcmp(command.command->flags, "-n") == 0)
		n = 1;
	if (!command.command->args[0])
	{
		if (!n)
			ft_putstr_fd("\n", 1);
		exit(0);
	}
	while (command.command->args[i])
	{
		ft_putstr_fd(command.command->args[i], 1);
		command.command->args[i + 1] ? ft_putstr_fd(" ", 1) : 0;
		++i;
	}
	!n ? ft_putstr_fd("\n", 1) : 0;
	exit (0);
}
