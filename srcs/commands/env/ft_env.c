/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:10:23 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/10 15:58:05 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

int		ft_env(t_list *env)
{
	t_list *tmp;

	while (env)
	{
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	return(0);
}
