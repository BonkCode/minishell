/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:34:27 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/26 23:46:47 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

int		ft_exit(t_simple_command command, char **environ)
{
	if (command.args->next && !str_is_num(command.args->next->content))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command.args->next->content, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (!command.piped)
			exit (2);
		else
			return (2);
	}
	else if (command.args->next && command.args->next->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (command.args->next)
	{
		if (!command.piped)
			exit (ft_atoi(command.args->next->content));
		else
			return (ft_atoi(command.args->next->content));
	}
	else
	{
		if (!command.piped)
			exit (0);
		else
			return (0);
	}
}
