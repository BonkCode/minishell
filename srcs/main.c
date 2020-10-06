/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:38:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 12:35:55 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"
#include "../ft_printf/libftprintf.h"

void	dummy_echo(t_command command) {ft_strlen(command.commands->command);}
void	dummy_cd(t_command command) {ft_strlen(command.commands->command);}
void	dummy_export(t_command command) {ft_strlen(command.commands->command);}
void	dummy_unset(t_command command) {ft_strlen(command.commands->command);}
void	dummy_env(t_command command) {ft_strlen(command.commands->command);}
void	dummy_exit(t_command command) {ft_strlen(command.commands->command);}

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

void		print_commands(t_command command)
{
	t_list	*arg_tmp;

	arg_tmp = NULL;
	ft_printf("return_status: %i\n", command.status);
	if (command.status != 0)
		return ;
	ft_printf("infile: %i\n", command.infile);
	ft_printf("outfile: %i\n", command.outfile);
	ft_printf("errfile: %i\n", command.errfile);
	ft_printf("========================\n");
	while (command.commands)
	{
		ft_printf("command: %s\n", command.commands->command);
		ft_printf("flag: %s\n", command.commands->flag);
		ft_printf("arguments: ");
		if (command.commands->arguments)
		{
			arg_tmp = command.commands->arguments;
			while (command.commands->arguments)
			{
				ft_printf("<%s> ", command.commands->arguments->content);
				command.commands->arguments = command.commands->arguments->next;
			}
			command.commands->arguments = arg_tmp;
		}
		ft_printf("\npiped: %i\n", command.commands->piped);
		command.commands = command.commands->next;
		ft_printf("-------------------\n");
	}
	ft_printf("========================\n");
}

int			main(void)
{
	char		*line;
	char		**tokens;
	int			i;
	int			command_flag;
	t_command	command;

	setup_commands(g_commands);
	while (1)
	{
		ft_putstr_fd("bibaibobabash-0.0.2$ ", 1);
		if (get_next_line(0, &line))
		{
			command.status = 127;
			command.infile = NULL;
			command.errfile = NULL;
			command.outfile = NULL;
			command.commands = NULL;
			i = -1;
			tokens = tokenize(line);
			command_flag = 0;
			while (++i < 7)
			{
				if (ft_strncmp(tokens[0], g_commands[i].name,
						ft_strlen(g_commands[i].name) + 1) == 0)
				{
					command_flag = 1;
					print_2d_arr(tokens);
					command = parse(tokens, g_commands);
					clear_tokens(tokens, -1);
					print_commands(command);
					break ;
				}
			}
			if (!command_flag)
				ft_putstr_fd("wrong command", 2);
			ft_putstr_fd("\n", 1);
			free(line);
			clear_command(&command.commands);
			if (command.infile)
			{
				free(command.infile);
				command.infile = NULL;
			}
			if (command.outfile)
			{
				free(command.outfile);
				command.outfile = NULL;
			}
			if (command.errfile)
			{
				free(command.errfile);
				command.errfile = NULL;
			}
		}
	}
	return (0);
}
