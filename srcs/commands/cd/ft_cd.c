/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:33:32 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/01 15:53:40 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"
#include <unistd.h>
#include <stdio.h>

void	ft_cd(t_command command)
{
	if (ft_strlen(command.command->arguments) == 1)
		chdir(command.command->arguments);

}

/*
int		main(int argc, char **av, char **env)
{
	t_command com;

	ft_pwd(com);
	ft_cd(com);
	ft_pwd(com);
	return (0);
}
*/
