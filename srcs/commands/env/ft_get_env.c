/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:19:39 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/06 16:42:22 by rvernius         ###   ########.fr       */
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
/*
int main(int ac, char **av, char **environ)
{
	t_list *env;

	env = NULL;
	ft_get_env(&env, environ);

	int i = 0;
	while (env)
	{
		printf("Aaaa");
		ft_printf("%s\n", env->content);
		env = env->next;
	}
	return(0);
}
*/