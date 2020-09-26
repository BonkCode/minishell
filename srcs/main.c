/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:38:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/26 17:26:58 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"

int	dummy_echo(t_command command) {return (ft_strlen(command.command));}
int	dummy_cd(t_command command) {return (ft_strlen(command.command));}
int	dummy_export(t_command command) {return (ft_strlen(command.command));}
int	dummy_unset(t_command command) {return (ft_strlen(command.command));}
int	dummy_env(t_command command) {return (ft_strlen(command.command));}
int	dummy_exit(t_command command) {return (ft_strlen(command.command));}

void		setup_commands(t_shell_cmd commands[7])
{
	(commands)[0] = new_shell_cmd("echo", &dummy_echo);
	(commands)[1] = new_shell_cmd("cd", &dummy_cd);
	(commands)[2] = new_shell_cmd("export", &dummy_export);
	(commands)[3] = new_shell_cmd("unset", &dummy_unset);
	(commands)[4] = new_shell_cmd("env", &dummy_env);
	(commands)[5] = new_shell_cmd("exit", &dummy_exit);
	(commands)[6] = new_shell_cmd("pwd", &dummy_exit);
}

t_shell_cmd	g_commands[7];
int			status = 0;

char		**lex(char *line)
{
	char **tokens;

	tokens = ft_split(line, ' ');
	return (tokens);
}

int			main(void)
{
	char	*line;
	char	**tokens;
	int		i;
	int		command_flag;

	setup_commands(g_commands);
	while (1)
	{
		ft_putstr_fd("bibaibobabash-0.0.1$ ", 1);
		if (get_next_line(0, &line))
		{
			tokens = lex(line);
			i = -1;
			command_flag = 0;
			while (++i < 7)
			{
				if (ft_strncmp(tokens[0], g_commands[i].name,
						ft_strlen(g_commands[i].name) + 1) == 0)
				{
					command_flag = 1;
					ft_putstr_fd(g_commands[i].name, 1);
					break ;
				}
			}
			if (!command_flag)
				ft_putstr_fd("wrong command", 1);
			ft_putstr_fd("\n", 1);
			free(line);
		}
	}
	return (0);
}
