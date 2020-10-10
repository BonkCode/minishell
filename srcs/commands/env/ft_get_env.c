/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:19:39 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/08 14:53:24 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_get_env(t_list **env, char **environ)
{
	int i;

	i = 0;
	while (environ[i])
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(environ[i])));
		++i;
	}
}
