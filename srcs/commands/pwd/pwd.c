/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:37:27 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/01 15:52:38 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_pwd(t_command command)
{
	char *buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	return (0);
}
