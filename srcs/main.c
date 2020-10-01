/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:38:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/01 13:07:07 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"

void	dummy_echo(t_command command) {ft_strlen(command.command->command);}
void	dummy_cd(t_command command) {ft_strlen(command.command->command);}
void	dummy_export(t_command command) {ft_strlen(command.command->command);}
void	dummy_unset(t_command command) {ft_strlen(command.command->command);}
void	dummy_env(t_command command) {ft_strlen(command.command->command);}
void	dummy_exit(t_command command) {ft_strlen(command.command->command);}

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

void		print_2d_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_putchar_fd('|', 1);
		ft_putstr_fd(str[i], 1);
		ft_putchar_fd('|', 1);
		ft_putchar_fd(' ', 1);
	}
}

void		free_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

int			main(void)
{
	char		*line;
	char		**tokens;
	int			i;
	int			command_flag;
//	t_command	command;

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
					//ft_putstr_fd(g_commands[i].name, 1);
					tokens = tokenize(line);
					print_2d_arr(tokens);
					free_tokens(tokens);
					//command.command->command = g_commands[i].name;
					//ft_putnbr_fd(g_commands[i].function(command), 1);
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
