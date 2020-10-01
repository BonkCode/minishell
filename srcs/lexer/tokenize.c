/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:12:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/29 15:40:18 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_token_count(char const *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			size++;
		if (str[i] == 34)
		{
			++i;
			while (str[i] != 34)
				++i;
		}
		else if (str[i] == 39)
		{
			++i;
			while (str[i] != 39)
				++i;
		}
		while (str[i] != ' ' && str[i] != '\0')
			++i;
		if (str[i] != '\0')
			++i;
	}
	return (size);
}

static size_t	get_token_size(char const *str)
{
	size_t	size;

	size = 0;
	if (*str == 34 || *str == 39)
	{
		++size;
		while (str[size] != *str && str[size] != '\0')
			++size;
	}
	else
	{
		while (str[size] != ' ' && str[size] != '\0')
			++size;
	}
	return (size);
}

static char		*clear_tokens(char **tokens, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(tokens[i]);
	free(tokens);
	return (NULL);
}

static void		proceed_to_next_token(char const *str)
{
	char	qmark;
	
	if (*str == 34 || *str == 39)
	{
		qmark = *str
		++str;
		while (*str != qmark && *str != '\0')
			++size;
	}
	else
	{
		while (str[size] != ' ' && str[size] != '\0')
			++size;
	}
	return (size);
}

char			**tokenize(char const *str)
{
	char	**tokens;
	size_t	i;
	size_t	size;

	if (!str)
		return (NULL);
	size = get_token_count(str);
	tokens = malloc((size + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (*str)
	{
		size = get_token_size(str);
		if (size > 0)
		{
			tokens[i] = malloc((size + 1) * sizeof(char));
			if (!tokens[i])
				return (clear_tokens(tokens, i - 1));
			tokens[i][size] = '\0';
			ft_strlcpy(tokens[i], str, size + 1);
			++i;
		}
		proceed_to_next_token(&str);
	}
	return (tokens);
}
