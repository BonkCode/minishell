/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:17:59 by rvernius          #+#    #+#             */
/*   Updated: 2020/12/27 17:27:26 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../libft/libftprintf.h"
# include "m_types.h"
# include "c_types.h"

int		dummy_echo(t_simple_command command, char **environ);
int		dummy_cd(t_simple_command command, char **environ);
int		dummy_export(t_simple_command command, char **environ);
int		dummy_unset(t_simple_command command, char **environ);
int		dummy_env(t_simple_command command, char **environ);
int		dummy_exit(t_simple_command command, char **environ);
int		ft_exit(t_simple_command command, char **environ);
int		ft_echo(t_simple_command command, char **environ);
int		ft_pwd(t_simple_command command, char **environ);
int		ft_cd(t_simple_command command, char **environ);
int		ft_env(t_simple_command command, char **environ);
int		ft_exit(t_simple_command command, char **environ);
int		ft_export(t_simple_command command, char **environ);
int		ft_unset(t_simple_command command, char **environ);
int		dummy_pwd(t_simple_command command, char **environ);
void	ft_get_env(t_list **env, char **environ);

#endif
