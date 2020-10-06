/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_clearer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:25:59 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 15:26:15 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"

char		**clear_tokens(char **tokens, int count)
{
	int	i;

	i = -1;
	if (count < 0)
	{
		while (tokens[++i])
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
	}
	else
	{
		while (++i < count)
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
	}
	free(tokens);
	tokens = NULL;
	return (NULL);
}
