/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:57:24 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/01 14:50:01 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

void		ft_unset(char *arg, char **environ)
{
	int i;
	int j;
	char **split_re;

	i = 0;
	j = 0;

	while (environ[j])
	{
		split_re = ft_split(environ[j], '=');
		if (split_re)
		{
			if(ft_strncmp(split_re[0], arg, ft_strlen(environ[i])) == 0)
			{
				printf("%s\n", split_re[0]);
				printf("%s\n", environ[j]);
				free(environ[j]);
				environ[j] = NULL;
			}
		}
		++j;
	}
}
