/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:26:29 by rvernius          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/10/08 15:18:47 by rtrant           ###   ########.fr       */
=======
/*   Updated: 2020/10/01 15:50:32 by rvernius         ###   ########.fr       */
>>>>>>> master
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
