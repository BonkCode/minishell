/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:45:12 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/26 16:21:42 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEXER_H
# define FLEXER_H
# include "libft.h"
#include "m_types.h"

t_shell_cmd	new_shell_cmd(char *name, int (*func)(t_command command));

#endif
