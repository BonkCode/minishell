/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:37:27 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/29 13:28:17 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/commands.h"

int		ft_pwd(t_command command)
{
	char *buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	return (0);
}
