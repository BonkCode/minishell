/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:19:11 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/31 19:26:25 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

extern int	g_start_env_len;

void			insert_value(int *i, char *token, char **environ,
						char *to_insert)
{
	if (!ft_strchr(token, '='))
		*i = -1;
	else if (*i > g_start_env_len)
	{
		free(environ[*i]);
		environ[*i] = ft_strdup(to_insert);
	}
	else
	{
		ft_strlcpy(environ[*i], to_insert,
				ft_strlen(to_insert) + 1);
	}
	*i = -1;
}

void			export_var(t_simple_command command, char *to_insert,
						char **environ, char *var_name)
{
	int		i;
	char	**env_split;

	i = -1;
	while (environ[++i] && !command.piped)
	{
		env_split = ft_split(environ[i], '=');
		if (!ft_strncmp(env_split[0], var_name,
			ft_strlen(env_split[0]) + 1))
		{
			insert_value(&i, command.args->content, environ, to_insert);
			clear_tokens(env_split, -1);
			break ;
		}
		clear_tokens(env_split, -1);
	}
	if (i > 0 && !command.piped)
	{
		environ[i] = ft_strdup(to_insert);
		environ[i + 1] = NULL;
	}
}

static char		*get_var_value(char *str)
{
	char	*value;

	if (!ft_strchr(str, '=') ||
		*(ft_strchr(str, '=') + 1) == '\0' ||
		*ft_strchr(str, '=') == ' ')
	{
		value = ft_strdup("");
	}
	else
	{
		value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	return (value);
}

static void		get_var_name(char **var_name, int *return_value, char *token)
{
	int	i;

	i = -1;
	*var_name = copy_till_char(token, '=');
	while ((*var_name)[++i])
	{
		if ((!ft_isalnum((*var_name)[i]) && (*var_name)[i] != '_') ||
			(ft_isdigit((*var_name)[i]) && i == 0))
			break ;
	}
	if ((*var_name)[0] == '\0' || (*var_name)[i] != '\0')
	{
		ft_putstr_fd("minishell: export: \'", 1);
		ft_putstr_fd(token, 1);
		ft_putstr_fd(": not a valid identifier\n", 1);
		free((*var_name));
		(*var_name) = NULL;
		*return_value = 1;
	}
}

int				ft_export(t_simple_command command, char **environ)
{
	int		return_value;
	char	*var_name;
	char	*var_value;
	char	*to_insert;

	return_value = 0;
	while (command.args->next)
	{
		command.args = command.args->next;
		get_var_name(&var_name, &return_value, command.args->content);
		if (!var_name)
		{
			free(var_name);
			continue ;
		}
		var_value = get_var_value(command.args->content);
		to_insert = ft_strjoin(var_name, "=");
		to_insert = ft_strjoin_gnl(to_insert, var_value);
		export_var(command, to_insert, environ, var_name);
		free(to_insert);
		free(var_value);
		free(var_name);
	}
	return (return_value);
}
