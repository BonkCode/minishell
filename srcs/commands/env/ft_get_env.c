/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:19:39 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/11 14:38:47 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "libftprintf.h"

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
