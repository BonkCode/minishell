/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:10:23 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/01 13:56:38 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_env(char **environ)
{
	int i;

	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], 1);
		++i;
	}
	exit(0);
}
