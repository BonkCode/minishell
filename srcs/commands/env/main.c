/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:15:38 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/06 17:26:13 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/commands.h"

int		ft_env(t_list *env);
void	ft_unset(t_list *env, char *arg);
void	ft_get_env(t_list **env, char **environ);

int		main(int argc, char **av, char **environ)
{
	t_list *env;

	env = NULL;
	ft_get_env(&env, environ);
	//ft_env(env);
	//ft_env(env);
	//ft_env(env);
	ft_unset(env, "b");
	ft_env(env);
	return (0);
}
