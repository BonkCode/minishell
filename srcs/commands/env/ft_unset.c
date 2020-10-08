/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:57:24 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/06 17:29:38 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_unset(t_list *env, char *arg)
{
	t_list	*prev;
	char	**split_re;

	prev = env;
	env = env->next;
	while (env)
	{
		split_re = ft_split(env->content, '=');
		if (split_re)
		{
			if (ft_strncmp(split_re[0], arg, ft_strlen(arg) + 1) == 0)
			{
				prev->next = env->next;
				ft_lstdelone(env, free);
				env = prev;
				break ;
			}
			else
			{
				prev = env;
				env = env->next;
			}
		}
	}
	//NEED TO FREE MEMORY
}
