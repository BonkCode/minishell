/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flexer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:45:12 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 20:00:25 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEXER_H
# define FLEXER_H
# include "libft.h"
# include "m_types.h"

t_shell_cmd			new_shell_cmd(char *name,
						int (*func)(t_simple_command command, char **environ));
char				**tokenize(char const *str);
char				***split_tokens_by_semicolons(char **tokens);
char				**clear_tokens(char **tokens, int count);
void				*clear_3d(char ****arr, int n, int k);
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
							char **tokens, int i, int *index);
void				get_redirect_files(char **tokens, int i,
							t_command *return_command);
void				clear_command(t_simple_command **simple_command);
t_tokens			new_t_token(char **tokens, int *i);
void				free_command(t_command *command);
int					expand(char ***tokens, t_list *env);
void				free_2_str(char **s1, char **s2);
void				expand_token(char **token, t_list *env);
int					handle_line(char **line, char **environ);
void				init_command(t_command *command);
void				get_command(t_command *command, int *command_flag,
								char **tokens);
void				glue_tokens(char ***tokens);
void				sigint_handler();
int					validate_tokens(char **tokens);
int					str_is_num(char *str);
char				*copy_till_char(char *str, char c);
int					str_is_num(char *str);
void				redirect_stdout(t_command command, int (*fd)[4]);
void				del(void *data);
void				redirect_stderr(t_command command, int (*fd)[4]);
int					return_normal(t_list **env, char **line,
								char ****split_tokens, char **tokens);
int					return_split_tokens_err(t_list **env,
									char **tokens, char **line);
int					return_syntax_error(int status, t_list **env,
										char **line, char **tokens);
int					return_token_alloc_error(char **line, t_list **env);
void				setup_pipe(int piped, int (*pipe_fd)[2], int fd);
void				copy_std(int (*std_copy)[3]);
void				init_fds(int (*fd)[4]);
void				restore_std_fd(int *fd, int std_fd);
void				restore_std(int (*std_copy)[3]);
void				sigint_skip(int c);
void				run_command(int command_flag, t_simple_command *command,
						char **environ);
void				run_executable(t_simple_command *command, char **environ);
void				redirect_pipes(int flush_flag, t_command command,
									t_pipe *pipe_fd);
void				flush_pipes(int flush_flag, t_command command,
									t_pipe *pipe_fd);
void				close_pipe(t_pipe *pipe_fd);
void				set_all_subcommands_pipe(t_command *command);
void				redirect_other(t_command command, int (*fd)[4]);
void				redirect_stdin(t_command command, int (*fd)[4]);
void				glue_tokens(char ***tokens);
void				init_command(t_command *command);
void				setup_commands(t_shell_cmd commands[7]);

#endif
