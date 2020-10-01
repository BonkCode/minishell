/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:46:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/01 12:17:22 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_TYPES_H
# define M_TYPES_H

typedef struct	s_simple_command
{
	char						*command;
	char						*flags;
	char						**arguments;
	struct s_simple_commamnd	*next;
}				t_simple_command;

typedef struct	s_command
{
	t_simple_command	*command;
	char				*infile;
	char				*outfile;
	char				*errfile;
}				t_command;

typedef struct	s_shell_cmd
{
	char		*name;
	void			(*function)(t_command command);
}				t_shell_cmd;

#endif
