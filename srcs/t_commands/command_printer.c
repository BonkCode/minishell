/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:31:39 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/14 22:36:04 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "m_types.h"

void		print_commands(t_command command)
{
	t_list	*arg_tmp;

	ft_printf("return_status: %i\n", command.status);
	ft_printf("infile: ");
	while (command.infile)
	{
		ft_printf("%s;   ", command.infile->content);
		command.infile = command.infile->next;
	}
	ft_printf("\noutfile: ");
	while (command.outfile)
	{
		ft_printf("%s;   ", command.outfile->content);
		command.outfile = command.outfile->next;
	}
	ft_printf("\nerrfile: ");
	while (command.errfile)
	{
		ft_printf("%s;   ", command.errfile->content);
		command.errfile = command.errfile->next;
	}
	ft_printf("\nother: ");
	while (command.other_files)
	{
		ft_printf("%s;   ", command.other_files->content);
		command.other_files = command.other_files->next;
	}
	ft_printf("\n========================\n");
	while (command.commands)
	{
		ft_printf("command: %s\nflag: %s\nargs: ",
				command.commands->command, command.commands->flag);
		if (command.commands->args)
		{
			arg_tmp = command.commands->args;
			while (command.commands->args)
			{
				ft_printf("<%s> ", command.commands->args->content);
				command.commands->args = command.commands->args->next;
			}
			command.commands->args = arg_tmp;
		}
		ft_printf("\npiped: %i\n", command.commands->piped);
		command.commands = command.commands->next;
		ft_printf("-------------------\n");
	}
	ft_printf("========================\n");
}
