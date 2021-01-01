/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:12:22 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/01 22:41:57 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

int		ft_pwd(t_simple_command command, char **environ)
{
	char	dir[100];

	getcwd(dir, 100);
	ft_putendl_fd(dir, 1);
	return (0);
}
