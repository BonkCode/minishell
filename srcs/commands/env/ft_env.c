/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:10:23 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/06 16:49:09 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_env(t_list *env)
{
	while (env)
	{
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	exit(0);
}
