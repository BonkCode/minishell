/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:04:00 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/09 17:07:00 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	get_words_count(char const *s, char c)
{
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (0);
	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			size++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			i++;
	}
	return (size);
}

static	size_t	get_word_size(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] != c && s[size] != '\0')
		size++;
	return (size);
}

static	void	proceed_to_next_word(char const **s, char c)
{
	while (**s != c && **s != '\0')
		(*s)++;
	while (**s == c && **s != '\0')
		(*s)++;
}

static char		**free_array(char **list, int size)
{
	while (size >= 0)
	{
		free((void *)list[size]);
	}
	free(list);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	size;

	size = get_words_count(s, c);
	result = (char **)malloc((size + 1) * sizeof(char *));
	if (!result || !s)
		return (NULL);
	result[size] = NULL;
	i = 0;
	while (*s != '\0')
	{
		size = get_word_size(s, c);
		if (size > 0)
		{
			result[i] = (char *)malloc((size + 1) * sizeof(char));
			if (!result)
				return (free_array(result, i));
			result[i][size] = '\0';
			ft_strlcpy(result[i], s, size + 1);
			i++;
		}
		proceed_to_next_word(&s, c);
	}
	return (result);
}
