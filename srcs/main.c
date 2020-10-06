/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:38:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 12:33:33 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "flexer.h"
#include "m_types.h"

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

void		free_tokens(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void		print_commands(t_command command)
{
	ft_putstr_fd("return status: ", 1);
	ft_putnbr_fd(command.status, 1);
	ft_putstr_fd("\n", 1);
	if (command.status != 0)
		return ;
	ft_putstr_fd("infile: ", 1);
	ft_putstr_fd(command.infile, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("outfile: ", 1);
	ft_putstr_fd(command.outfile, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("errfile: ", 1);
	ft_putstr_fd(command.errfile, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("-------------------------\n", 1);
	while (command.commands)
	{
		ft_putstr_fd("command: ", 1);
		ft_putstr_fd(command.commands->command, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("flag: ", 1);
		ft_putstr_fd(command.commands->flag, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("arguments: ", 1);
		if (command.commands->arguments)
		{
			while (command.commands->arguments->next)
			{
				ft_putstr_fd(command.commands->arguments->content, 1);
				ft_putstr_fd(" ", 1);
				command.commands->arguments = command.commands->arguments->next;
			}
		}
		ft_putstr_fd("piped: ", 1);
		ft_putnbr_fd(command.commands->piped, 1);
		ft_putstr_fd("\n", 1);
		command.commands = command.commands->next;
	}
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
		ft_putstr_fd("bibaibobabash-0.0.1$ ", 1);
		if (get_next_line(0, &line))
		{
			command.status = 127;
			command.infile = NULL;
			command.errfile = NULL;
			command.outfile = NULL;
			command.commands = NULL;
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
					command = parse(tokens, g_commands);
					free_tokens(tokens);
					print_commands(command);
					ft_putnbr_fd(command.status, 1);
					//command.command->command = g_commands[i].name;
					//ft_putnbr_fd(g_commands[i].function(command), 1);
					break ;
				}
			}
			if (!command_flag)
				ft_putstr_fd("wrong command", 1);
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
