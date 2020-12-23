/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:33:32 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/10 16:57:27 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/m_types.h"
#include <unistd.h>
#include <stdio.h>

void	ft_cd(t_simple_command command, t_)
{
	if (ft_strlen(command.args) == 1)
		chdir(command.args);
	
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
