/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:31:04 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/13 18:29:30 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "flexer.h"

static int		count_and_alloc(char ****split_tokens, char **tokens)
{
	int	i;
	int	j;
	int	size;

	size = 1;
	i = -1;
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], ";", 2))
			++size;
	}
	if (!(*split_tokens = malloc(sizeof(char **) * (size + 1))))
		return (0);
	(*split_tokens)[size] = 0;
	return (size);
}

static int		alloc_2nd_dimension(char ****split_tokens,
						char **tokens, int size)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[j])
		++j;
	while (++i < size)
	{
		if (!((*split_tokens)[i] = ft_calloc(j + 1, sizeof(char *))))
		{
			j = -1;
			while (++j < i)
				clear_tokens((*split_tokens)[j], -1);
			return (0);
		}
	}
	return (1);
}

char			***split_tokens_by_semicolons(char **tokens)
{
	char	***split_tokens;
	int		size;
	int		i;
	int		j;

	if (!(size = count_and_alloc(&split_tokens, tokens)))
		return (NULL);
	if (!alloc_2nd_dimension(&split_tokens, tokens, size))
		return (NULL);
	size = 0;
	i = -1;
	j = -1;
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], ";", 2))
		{
			++size;
			j = -1;
			continue ;
		}
		split_tokens[size][++j] = ft_strdup(tokens[i]);
	}
	return (split_tokens);
}
