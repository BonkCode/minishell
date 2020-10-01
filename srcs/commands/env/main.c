/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:15:38 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/01 14:49:01 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_env(char **environ);
void	ft_unset(char *arg, char **environ);

int		main(int argc, char **av, char **environ)
{
	char *arg;

	arg = malloc(2);
	arg[0] = 'a';
	arg[1] = '\0';
	//ft_env(environ);
	ft_unset(arg, &*environ);
	ft_env(environ);
	return (0);
}
