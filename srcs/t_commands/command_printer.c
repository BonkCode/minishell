/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:31:39 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 17:09:30 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "m_types.h"

void		print_commands(t_command command)
{
	t_list	*arg_tmp;

	ft_printf("return_status: %i\n", command.status);
	ft_printf("infile: %s\noutfile: %s\nerrfile: %s\n",
			command.infile, command.outfile, command.errfile);
	ft_printf("========================\n");
	while (command.commands)
	{
		ft_printf("command: %s\nflag: %s\narguments: ",
				command.commands->command, command.commands->flag);
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
