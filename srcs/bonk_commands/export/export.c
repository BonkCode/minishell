/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:19:11 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/27 16:12:13 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

extern int	g_start_env_len;

static char		*copy_till_char(char *str, char c)
{
	int		size;
	char	*return_string;

	size = 0;
	while (str[size] && str[size] != c)
		++size;
	if (!(return_string = ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	ft_strlcpy(return_string, str, size + 1);
	return (return_string);
}

static char		*get_var_value(char *str)
{
	char	*value;
	
	if (!ft_strchr(str, '=') || *(ft_strchr(str, '=') + 1) == '\0' || *ft_strchr(str, '=') == ' ')
	{
		value = ft_strdup("");
	}
	else
	{
		value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	return (value);
}

int				ft_export(t_simple_command command, char **environ)
{
	int		return_value;
	int		i;
	int		env_i;
	char	**env_split;
	char	*var_name;
	char	*var_value;
	char	*to_insert;

	return_value = 0;
	command.args = command.args->next;
	while (command.args)
	{
		i = -1;
		var_name = copy_till_char(command.args->content, '=');
		while (var_name[++i])
		{
			if ((!ft_isalnum(var_name[i]) && var_name[i] != '_') || (ft_isdigit(var_name[i]) && i == 0))
				break ;
		}
		if (var_name[0] == '\0' || var_name[i] != '\0')
		{
			ft_putstr_fd("minishell: export: \'", 1);
			ft_putstr_fd(command.args->content, 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
			free(var_name);
			return_value = 1;
			command.args = command.args->next;
			continue ;
		}
		var_value = get_var_value(command.args->content);
		to_insert = ft_strjoin(var_name, "=");
		to_insert = ft_strjoin_gnl(to_insert, var_value);
		env_i = -1;
		while (environ[++env_i] && !command.piped)
		{
			env_split = ft_split(environ[env_i], '=');
			if (!ft_strncmp(env_split[0], var_name, ft_strlen(env_split[0]) + 1))
			{
				if (!ft_strchr(command.args->content, '='))
				{
					env_i = -1;
					break ;
				}
				if (env_i > g_start_env_len)
				{
					free(environ[env_i]);
					environ[env_i] = ft_strdup(to_insert);
				}
				else
				{
					ft_strlcpy(environ[env_i], to_insert, ft_strlen(to_insert) + 1);
				}
				env_i = -1;
				break ;
			}
		}
		if (env_i > 0 && !command.piped)
		{
			environ[env_i] = ft_strdup(to_insert);
			environ[env_i + 1] = NULL;
		}
		free(to_insert);
		free(var_value);
		free(var_name);
		command.args = command.args->next;
	}
	return (return_value);
}
