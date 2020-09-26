/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:46:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/26 15:43:59 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_TYPES_H
# define M_TYPES_H

typedef struct	s_command
{
	char		*command;
	char		*flags;
	char		**arguments;
	t_command	*next;
	char		*infile;
	char		*outfile;
	char		*errfile;
}				t_command;

typedef struct	s_shell_cmd
{
	char		*name;
	int			(function)(t_command command);
}				t_shell_cmd;

#endif
