/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 13:44:55 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/07 20:16:55 by rtrant           ###   ########.fr       */
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

static int	check_tokens(char **tokens, int redirected, int len)
{
	int	i;

	i = 0;
	while (i < len && tokens[i])
	{
		if (!ft_strncmp_split(tokens[i], "| > < >>", ' ') && !tokens[i + 1])
			return ((i << 8) + STAT_SYNTAX_ERR);
		else if (!ft_strncmp_split(tokens[i], "| ; < > >>", ' ')
				&& tokens[i + 1] &&
			!ft_strncmp_split(tokens[i + 2], "| ; < > >>", ' '))
			return (((i + 2) << 8) + STAT_DOUBLE_SPEC_TOKEN_ERR);
		else if (!ft_strncmp_split(tokens[i], "< > >>", ' ') && !tokens[i + 1])
			return ((i << 8) + STAT_SYNTAX_ERR);
		else if (!ft_strncmp_split(tokens[i], "< > >>", ' ') && tokens[i + 3] &&
			!ft_strncmp(tokens[i + 4], "|", 2))
			return ((i << 8) + STAT_DOUBLE_REDIRECTION_ERR);
		if (!ft_strncmp_split(tokens[i], "< > >>", ' '))
			redirected = 1;
		if (!ft_strncmp(tokens[i], "|", 2) && redirected)
			return ((i << 8) + STAT_DOUBLE_REDIRECTION_ERR);
		if (!ft_strncmp(tokens[i], ";", 2))
			redirected = 0;
		i += 2;
	}
	return (STAT_OK);
}

int			validate_tokens(char **tokens)
{
	int	i;
	int	len;
	int	redirected;

	i = 0;
	redirected = 0;
	len = get_2d_arr_len(tokens);
	if (!ft_strncmp_split(tokens[0], "; |", ' '))
		return ((0 << 8) + STAT_SYNTAX_ERR);
	return (check_tokens(tokens, redirected, len));
}
