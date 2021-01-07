/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:22:26 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 20:29:35 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

static char	*get_home_dir(char **environ)
{
	char	*home_str;
	char	**split_env;
	t_list	*env;
	t_list	*env_start;

	env = NULL;
	ft_get_env(&env, environ);
	env_start = env;
	while (env)
	{
		split_env = ft_split(env->content, '=');
		if (!ft_strncmp(split_env[0], "HOME", 5))
			break ;
		clear_tokens(split_env, -1);
		env = env->next;
	}
	ft_lstclear(&env_start, del);
	if (ft_strncmp(split_env[0], "HOME", 5))
		return (NULL);
	home_str = ft_strdup(split_env[1]);
	clear_tokens(split_env, -1);
	return (home_str);
}

int			ft_cd(t_simple_command command, char **environ)
{
	char				*home_dir;
	char				cwd[1024];
	t_simple_command	*s_c;

	if (command.piped)
		return (0);
	if (command.args->next && command.args->next->next)
	{
		return (1);
	}
	if (!(home_dir = get_home_dir(environ)))
		home_dir = ft_strdup("/");
	if (!command.args->next)
		chdir(home_dir);
	else
		chdir(command.args->next->content);
	getcwd(cwd, 1023);
	cwd[1023] = '\0';
	s_c = new_simple_command();
	ft_lstadd_back(&s_c->args, ft_lstnew(ft_strdup("export")));
	ft_lstadd_back(&s_c->args, ft_lstnew(ft_strjoin("PWD=", cwd)));
	ft_export(*s_c, environ);
	clear_simple_commands(&s_c);
	free(home_dir);
	return (0);
}
