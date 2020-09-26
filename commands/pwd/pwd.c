/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 15:37:27 by rvernius          #+#    #+#             */
/*   Updated: 2020/09/26 17:16:09 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <

int ft_pwd(t)
{
	char *buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	return (0);
}

