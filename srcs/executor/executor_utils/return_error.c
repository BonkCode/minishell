/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:25:47 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 19:23:55 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"
#include "libftprintf.h"

int			return_token_alloc_error(char **line, t_list **env)
{
	if ((*line)[0])
		ft_putstr_fd("minishell: failed to create tokens from input\n", 2);
	ft_lstclear(env, del);
	free(*line);
	return (-1);
}

int			return_syntax_error(int status, t_list **env,
								char **line, char **tokens)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(tokens[status >> 8], 2);
	ft_putstr_fd("'\n", 2);
	clear_tokens(tokens, -1);
	ft_lstclear(env, del);
	free(*line);
	return (status & 0xff00);
}

int			return_split_tokens_err(t_list **env, char **tokens, char **line)
{
	clear_tokens(tokens, -1);
	ft_lstclear(env, del);
	free(*line);
	return (-2);
}

int			return_normal(t_list **env, char **line, char ****split_tokens,
						char **tokens)
{
	free(*line);
	*line = NULL;
	ft_lstclear(env, del);
	clear_tokens(tokens, -1);
	clear_3d(split_tokens, -1, -1);
	return (0);
}

int			cmd_not_found(t_list **path, char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_lstclear(path, del);
	return (127);
}
