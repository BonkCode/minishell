/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:17:59 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/10 17:04:22 by rtrant           ###   ########.fr       */
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

void		dummy_echo(t_command command);
void		dummy_cd(t_command command);
void		dummy_export(t_command command);
void		dummy_unset(t_command command);
void		dummy_env(t_command command);
void		dummy_exit(t_command command);
void		ft_echo(t_command command);
void		ft_pwd(t_command command);
void		ft_cd(t_command command);
void		ft_exit(t_command command);
void		ft_get_env(t_list **env, char **environ);

#endif
