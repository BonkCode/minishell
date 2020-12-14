/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 13:44:55 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/14 21:47:46 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation_res.h"
#include "flexer.h"
#include "libftprintf.h"

static int	get_2d_arr_len(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		++len;
	return (len);
}

int	validate_tokens(char **tokens)
{
	int	i;
	int	len;
	int	redirected;

	i = 0;
	redirected = 0;
	len = get_2d_arr_len(tokens);
	if (!ft_strncmp(tokens[0], ";", 2))
		return ((0<<8) + STAT_SYNTAX_ERR);
	while (tokens[i] && i < len)
	{
		if (!ft_strncmp(tokens[i], "|", 2) && !tokens[i + 1])
			return ((i<<8) + STAT_SYNTAX_ERR);
		else if (!ft_strncmp_split(tokens[i], "| ; < > >>", ' ') && !ft_strncmp_split(tokens[i + 2], "| ; < > >>", ' '))
			return (((i + 2) << 8) + STAT_DOUBLE_SPEC_TOKEN_ERR);
		else if (!ft_strncmp_split(tokens[i], "< > >>", ' ') && !tokens[i + 1])
			return ((i<<8) + STAT_SYNTAX_ERR);
		else if (!ft_strncmp_split(tokens[i], "< > >>", ' ') && tokens[i + 3] && !ft_strncmp(tokens[i + 4], "|", 2))
			return ((i<<8) + STAT_DOUBLE_REDIRECTION_ERR);
		if (!ft_strncmp_split(tokens[i], "< > >>", ' '))
			redirected = 1;
		if (!ft_strncmp_split(tokens[i], "< > >> |", ' ') && redirected)
			return ((i<<8) + STAT_DOUBLE_REDIRECTION_ERR);
		if (!ft_strncmp(tokens[i], ";", 2))
			redirected = 0;
		i += 2;
	}
	return (STAT_OK);
}