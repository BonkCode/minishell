/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:45:12 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 17:16:41 by rtrant           ###   ########.fr       */
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
t_simple_command	*clear_simple_commands(t_simple_command **command);
void				print_commands(t_command command);
void				print_2d(char **arr);
void				free_command(t_command *command);

#endif
