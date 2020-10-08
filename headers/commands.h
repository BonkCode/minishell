/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:17:59 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/08 17:00:56 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "m_types.h"

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

#endif
