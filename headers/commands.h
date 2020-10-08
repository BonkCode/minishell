/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 16:17:59 by rvernius          #+#    #+#             */
/*   Updated: 2020/10/08 15:17:37 by rvernius         ###   ########.fr       */
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
//# include "flexer.h"

//char		**clear_tokens(char **tokens, int count);
void		ft_echo(t_command command);
void		ft_pwd(t_command command);
void		ft_cd(t_command command);
void		ft_exit(t_command command);

#endif
