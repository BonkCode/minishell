/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:09:56 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/16 18:26:02 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

extern int	g_start_env_len;

int		validate_var_name(char *var_name, int *return_value, char *token)
{
	int		i;

	i = -1;
	while (var_name[++i])
	{
		if ((!ft_isalnum(var_name[i]) && var_name[i] != '_') ||
			(ft_isdigit(var_name[i]) && i == 0))
			break ;
	}
	if (var_name[0] == '\0' || var_name[i] != '\0')
	{
		ft_putstr_fd("minishell: export: \'", 1);
		ft_putstr_fd(token, 1);
		ft_putstr_fd(": not a valid identifier\n", 1);
		*return_value = 1;
		return (0);
	}
	return (1);
}

void	shift_vars(char **environ, int i)
{
	if (i < g_start_env_len)
	{
		if (environ[i + 1])
			ft_strlcpy(environ[i], environ[i + 1],
					ft_strlen(environ[i + 1]) + 1);
		else
			environ[i] = NULL;
	}
	else
	{
		free(environ[i]);
		if (environ[i + 1])
			environ[i] = ft_strdup(environ[i + 1]);
		else
			environ[i] = NULL;
	}
}

void	unset_var(char **environ, t_simple_command command,
				char *var_name)
{
	int		i;
	char	**env_split;

	i = -1;
	env_split = NULL;
	while (environ[++i] && !command.piped)
	{
		env_split = ft_split(environ[i], '=');
		if (!ft_strncmp(env_split[0], var_name,
				ft_strlen(env_split[0]) + 1))
		{
			while (environ[i])
			{
				shift_vars(environ, i);
				++i;
			}
			clear_tokens(env_split, -1);
			break ;
		}
		clear_tokens(env_split, -1);
	}
}

int		ft_unset(t_simple_command command, char **environ)
{
	int		return_value;
	char	*var_name;

	while (command.args->next)
	{
		command.args = command.args->next;
		var_name = (char*)command.args->content;
		if (!validate_var_name(var_name, &return_value, command.args->content))
			continue ;
		unset_var(environ, command, var_name);
	}
	return (return_value);
}
