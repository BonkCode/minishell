/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:12:22 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/31 19:26:27 by rtrant           ###   ########.fr       */
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
	ft_putstr_fd(dir, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
