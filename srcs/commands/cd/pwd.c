/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:37:27 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/10 17:21:44 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void	ft_pwd(t_command command)
{
	char		*buf;
	int			i;

	i = 0;
	while (command.commands->args)
	{
		++i;
		command.commands->args = command.commands->args->next;
	}
	--i;
	if (i > 0)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		exit(1);
	}
	else
	{
		buf = getcwd(NULL, 0);
		ft_putendl_fd(buf, 1);
	}
	exit(0);
}
