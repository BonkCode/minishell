/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:36:54 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 19:25:57 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

extern int	g_status;

static char		**form_args(t_list *args)
{
	char	**return_args;
	int		i;

	i = -1;
	if (!(return_args = ft_calloc(ft_lstsize(args) + 1, sizeof(char *))))
		return (NULL);
	while (args)
	{
		return_args[++i] = ft_strdup(args->content);
		args = args->next;
	}
	return (return_args);
}

static t_list	*get_path(char **environ)
{
	int		i;
	t_list	*path;
	char	**split_var;
	char	**paths;

	i = -1;
	while (environ[++i])
	{
		split_var = ft_split(environ[i], '=');
		if (!ft_strncmp(split_var[0], "PATH", 5))
			break ;
		clear_tokens(split_var, -1);
		split_var = NULL;
	}
	if (!split_var)
		return (NULL);
	path = NULL;
	paths = ft_split(split_var[1], ':');
	i = -1;
	while (paths && paths[++i])
		ft_lstadd_back(&path, ft_lstnew(ft_strjoin(paths[i], "/")));
	if (paths)
		clear_tokens(paths, -1);
	clear_tokens(split_var, -1);
	return (path);
}

static int		launch_with_path_var(t_list *path, char **environ,
								char **args, t_simple_command *command)
{
	int		executed;
	char	*command_path;

	executed = 0;
	while (path)
	{
		command_path = ft_strjoin(path->content, command->command);
		if ((executed = execve(command_path,
							args, environ)) >= 0)
		{
			free(command_path);
			break ;
		}
		free(command_path);
		path = path->next;
	}
	return (executed);
}

static int		init_vars(int *executed, char ***args, t_list **path,
						t_simple_command *command)
{
	*executed = -1;
	if (!(*args = form_args(command->args)))
		return (-1);
	signal(SIGINT, sigint_skip);
	*path = NULL;
	return (0);
}

void			run_executable(t_simple_command *command, char **environ)
{
	pid_t	id;
	char	**args;
	t_list	*path;
	int		executed;

	if (init_vars(&executed, &args, &path, command) < 0)
		return ;
	if (!(id = fork()))
	{
		path = get_path(environ);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ft_strchr(command->command, '/'))
			executed = execve(command->command, args, environ);
		if (executed < 0 &&
			launch_with_path_var(path, environ, args, command) < 0)
			exit(cmd_not_found(&path, command->command));
		ft_lstclear(&path, del);
		exit(0);
	}
	else
		wait(&g_status);
	clear_tokens(args, -1);
	signal(SIGINT, sigint_handler);
}
