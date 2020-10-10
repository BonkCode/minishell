/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:45:12 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/10 17:04:12 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEXER_H
# define FLEXER_H
# include "libft.h"
# include "m_types.h"

t_shell_cmd			new_shell_cmd(char *name, void (*func)(t_command command));
char				**tokenize(char const *str);
char				**clear_tokens(char **tokens, int count);
t_command			parse(char **tokens);
t_simple_command	*clear_simple_commands(t_simple_command **command);
void				print_commands(t_command command);
void				print_2d(char **arr);
t_simple_command	*new_simple_command(void);
void				ft_command_add_back(t_simple_command **lst,
											t_simple_command *new);
void				init_return_command(t_command *return_command);
int					ft_strncmp_split(char *s1, char *s2, char c);
t_command			abort_parsing(t_command *return_command, int code,
					t_simple_command **simple_command, t_simple_command **list);
int					get_shell_cmd(t_simple_command **simple_command,
							char **tokens, int i);
void				get_redirect_files(char **tokens, int i,
							t_command *return_command);
void				clear_command(t_simple_command **simple_command);
t_tokens			new_t_token(char **tokens, int i);
void				free_command(t_command *command);
int					expand(char ***tokens, t_list *env);
int					delete_qmarks(char **token);
void				get_var_value(char *name, char **value, t_list *env);
void				get_var_name(int flag, char **var_name,
									char **token, int *i);
void				change_value(char *token_temp, char **token,
									t_var var, int i);
void				expand_token(char **token, t_list *env);

#endif
