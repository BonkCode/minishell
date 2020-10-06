/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:45:12 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/02 15:53:24 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEXER_H
# define FLEXER_H
# include "libft.h"
# include "m_types.h"

t_shell_cmd			new_shell_cmd(char *name, void (*func)(t_command command));
char				**tokenize(char const *str);
char				**clear_tokens(char **tokens, int count);
t_command			parse(char **tokens, t_shell_cmd cmds[7]);
t_simple_command	*clear_command(t_simple_command **command);

#endif
