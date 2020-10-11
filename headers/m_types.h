/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:46:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/11 14:30:20 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_TYPES_H
# define M_TYPES_H
# include "libftprintf.h"

typedef struct s_simple_command	t_simple_command;

struct			s_simple_command
{
	char				*command;
	char				*flag;
	t_list				*args;
	int					piped;
	t_simple_command	*next;
};

typedef struct	s_tokens
{
	char		**tokens;
	int			i;
}				t_tokens;

typedef struct	s_var
{
	char		*name;
	char		*value;
	int			len;
}				t_var;

typedef struct	s_command
{
	t_simple_command	*commands;
	char				*infile;
	char				*outfile;
	char				*errfile;
	int					status;
}				t_command;

typedef struct	s_shell_cmd
{
	char		*name;
	void		(*function)(t_command command);
}				t_shell_cmd;

#endif
