/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glue.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:54:34 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 20:01:29 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "flexer.h"

static void	copy_non_empty(char ***tokens, int size)
{
	int		i;
	char	**temp_2;

	if (!(temp_2 = ft_calloc(sizeof(char *), (size / 2 + 2))))
	{
		clear_tokens(*tokens, -1);
		return ;
	}
	i = -1;
	size = -1;
	while ((*tokens)[++i])
	{
		if (ft_strncmp((*tokens)[i], "", 1))
		{
			if (!(temp_2[++size] = ft_strdup((*tokens)[i])))
			{
				clear_tokens(temp_2, size);
				break ;
			}
		}
	}
	clear_tokens(*tokens, -1);
	*tokens = temp_2;
}

static void	glue_2_tokens(char ***tokens, int *i)
{
	char	*temp;

	if (ft_strncmp_split((*tokens)[*i], "; | < > >>", ' ') &&
		(*tokens)[*i + 1] &&
		ft_strncmp_split((*tokens)[*i + 2], "; | < > >>", ' '))
	{
		temp = (*tokens)[*i + 2];
		(*tokens)[*i + 2] = ft_strjoin((*tokens)[*i], (*tokens)[*i + 2]);
		free(temp);
		temp = (*tokens)[*i];
		(*tokens)[*i] = ft_strdup("");
		free(temp);
	}
}

void		glue_tokens(char ***tokens)
{
	char	*temp;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while ((*tokens)[++i])
		++size;
	i = 0;
	while (i < size - 1 && (*tokens)[i])
	{
		if (ft_strncmp((*tokens)[i + 1], " ", 2))
			glue_2_tokens(tokens, &i);
		else
		{
			temp = (*tokens)[i + 1];
			(*tokens)[i + 1] = ft_strdup("");
			free(temp);
		}
		i += 2;
	}
	copy_non_empty(tokens, size);
}
