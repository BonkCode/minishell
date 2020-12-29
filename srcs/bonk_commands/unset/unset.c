/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:09:56 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/27 17:27:05 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_types.h"
#include "libftprintf.h"
#include "flexer.h"
#include "commands.h"

extern int	g_start_env_len;

int		ft_unset(t_simple_command command, char **environ)
{
	int		i;
	int		return_value;
	char	*var_name;
	char	**env_split;
	
	command.args = command.args->next;
	while (command.args)
	{
		var_name = (char*)command.args->content;
		i = -1;
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
			return_value = 1;
			command.args = command.args->next;
			continue ;
		}
		i = -1;
		while (environ[++i] && !command.piped)
		{
			env_split = ft_split(environ[i], '=');
			if (!ft_strncmp(env_split[0], var_name, ft_strlen(env_split[0]) + 1))
			{
				while (environ[i])
				{
					if (i <= g_start_env_len)
					{
						if (environ[i + 1])
							ft_strlcpy(environ[i], environ[i + 1], ft_strlen(environ[i + 1]) + 1);
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
					++i;
				}
				break ;
			}
			clear_tokens(env_split, -1);
		}
		command.args = command.args->next;
	}
	return (return_value);
}
