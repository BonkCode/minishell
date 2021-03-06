/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_types.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:46:00 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:21:05 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_TYPES_H
# define M_TYPES_H
# include "libftprintf.h"
# define READ_END 0
# define WRITE_END 1

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
	int			*i;
}				t_tokens;

typedef struct	s_var
{
	char		*name;
	char		*value;
	int			len;
}				t_var;

typedef struct	s_fd_redir
{
	int			fd_out;
	int			fd_in;
	int			fd_err;
	int			fd_other;
	int			fd_out_dup;
	int			fd_in_dup;
	int			fd_err_dup;
}				t_files_redir;

typedef struct	s_command
{
	t_simple_command	*commands;
	t_list				*infile;
	t_list				*outfile;
	t_list				*errfile;
	t_list				*other_files;
	int					append;
	int					piped;
	int					status;
}				t_command;

typedef struct	s_shell_cmd
{
	char		*name;
	int			(*function)(t_simple_command command, char **environ);
}				t_shell_cmd;

typedef struct	s_pipe
{
	int			fd_1[2];
	int			fd_2[2];
}				t_pipe;

#endif
