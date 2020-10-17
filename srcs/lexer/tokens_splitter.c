/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:31:04 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/17 15:49:14 by rtrant           ###   ########.fr       */
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

static char		***trim_2d(char ***arr, int len)
{
	char	***res;
	int		i;
	int		j;
	int		end;
	int		n;
	int		size;

	i = 0;
	while (arr[i])
		++i;
	res = ft_calloc(sizeof(char **), i + 1);
	i = -1;
	while (arr[++i])
	{
		size = 0;
		j = -1;
		while (arr[i][size])
			++size;
		if (!ft_strncmp(arr[i][size - 1], "", 1) || !ft_strncmp(arr[i][size - 1], " ", 2))
			--size;
		end = size;
		if (!ft_strncmp(arr[i][0], "", 1) || !ft_strncmp(arr[i][0], " ", 2))
		{
			--size;
			++j;
		}
		res[i] = ft_calloc(sizeof(char *), size + 1);
		n = -1;
		while (arr[i][++j] && j < end)
			res[i][++n] = ft_strdup(arr[i][j]);
	}
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
			free(arr[i][j]);
		free(arr[i]);
	}
	free(arr);
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
			continue ;
		}
		split_tokens[size][++j] = ft_strdup(tokens[i]);
	}
	split_tokens = trim_2d(split_tokens, len);
	return (split_tokens);
}