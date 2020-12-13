/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:31:04 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/12 14:33:34 by rtrant           ###   ########.fr       */
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
		if (!ft_strncmp(tokens[i], ";", 2) && tokens[i + 1])
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
			clear_3d(split_tokens, i, -1);
			return (0);
		}
	}
	return (1);
}

static void		get_size_and_bounds(int *size, int *j, char ***arr, int *end)
{
	*size = 0;
	*j = -1;
	while ((*arr)[*size])
		++(*size);
	if (!ft_strncmp((*arr)[*size - 1], "", 1) ||
		!ft_strncmp((*arr)[*size - 1], " ", 2))
		--(*size);
	*end = *size;
	if (!ft_strncmp((*arr)[0], "", 1) || !ft_strncmp((*arr)[0], " ", 2))
	{
		--(*size);
		++(*j);
	}
}

static char		***trim_2d(char ****arr, int len)
{
	char	***res;
	int		i;
	int		j;
	int		end;
	int		size;

	i = 0;
	while ((*arr)[i])
		++i;
	if (!(res = ft_calloc(sizeof(char **), i + 1)))
		return (NULL);
	i = -1;
	while ((*arr)[++i])
	{
		get_size_and_bounds(&size, &j, (*arr) + i, &end);
		if (!(res[i] = ft_calloc(sizeof(char *), size + 1)))
			return (clear_3d(&res, i, -1));
		size = -1;
		while ((*arr)[i][++j] && j < end)
			if (!(res[i][++size] = ft_strdup((*arr)[i][j])))
				return (clear_3d(&res, i, j));
	}
	clear_3d(arr, -1, -1);
	return (res);
}

char			***split_tokens_by_semicolons(char **tokens)
{
	char	***split_tokens;
	int		size;
	int		i;
	int		j;
	int		len;

	if (!(size = count_and_alloc(&split_tokens, tokens)))
		return (NULL);
	if (!alloc_2nd_dimension(&split_tokens, tokens, size))
		return (NULL);
	len = size;
	size = 0;
	i = -1;
	j = -1;
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], ";", 2))
		{
			++size;
			j = -1;
		}
		else
			split_tokens[size][++j] = ft_strdup(tokens[i]);
	}
	return (trim_2d(&split_tokens, len));
}
