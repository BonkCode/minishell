/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:12:22 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/26 23:18:54 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

int		ft_pwd(t_simple_command command, char **environ)
{
	char	*dir;
	
	dir = getcwd(dir, 1000);
	ft_putstr_fd(dir, 1);
	free(dir);
	ft_putchar_fd('\n', 1);
	return (0);
}
