/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:22:26 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/31 19:26:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

static void	del(void *data)
{
	if (data)
		free(data);
	data = NULL;
}

static char	*get_home_dir(char **environ)
{
	char	*home_str;
	char	**split_env;
	t_list	*env;

	env = NULL;
	ft_get_env(&env, environ);
	while (env)
	{
		split_env = ft_split(env->content, '=');
		if (!ft_strncmp(split_env[0], "HOME", 5))
			break ;
		clear_tokens(split_env, -1);
		env = env->next;
	}
	if (ft_strncmp(split_env[0], "HOME", 5))
		return (NULL);
	home_str = ft_strdup(split_env[1]);
	clear_tokens(split_env, -1);
	ft_lstclear(&env, del);
	return (home_str);
}

int			ft_cd(t_simple_command command, char **environ)
{
	char	*home_dir;

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
	free(home_dir);
	return (0);
}
