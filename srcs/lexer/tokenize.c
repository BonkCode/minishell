/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:12:23 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/13 18:16:19 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "m_types.h"
#include "flexer.h"

static	int		skip_qmark(size_t *i, size_t *size, const char *str)
{
	int	qmark;

	if (str[*i] == 34 || str[*i] == 39)
	{
		qmark = str[*i];
		++(*i);
		while (str[*i] != qmark)
		{
			if (str[*i] == '\0')
				return (-2);
			++(*i);
		}
		if (str[*i + 1] != '\0' && str[*i + 1] != ' ')
			++(*size);
		++(*i);
	}
	return (0);
}

static size_t	get_token_count(char const *str)
{
	size_t	i;
	size_t	size;

	if (!str)
		return (-2);
	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			++size;
		if (ft_strchr(";|<>", str[i]))
		{
			i += ft_strchr("<>", str[i]) && str[i] == str[i + 1] ? 2 : 1;
			continue ;
		}
		if (skip_qmark(&i, &size, str) < 0)
			return (-2);
		while (!ft_strchr("'\";| ><", str[i]) && str[i] != '\0')
			++i;
		if (str[i] != '\0' && str[i] == ' ')
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
		if (str[size] != '\0')
			++size;
	}
	else if (ft_strchr("<>", *str) && *(str + 1) == *str)
		return (2);
	else if (ft_strchr(";|<>", *str))
		return (1);
	else
	{
		while (!ft_strchr("\'\";| <>", str[size]) && str[size] != '\0')
			++size;
	}
	return (size);
}

static void		proceed_to_next_token(char const **str)
{
	while (**str == ' ' && **str != '\0')
		++(*str);
}

char			**tokenize(char const *str)
{
	char	**tokens;
	size_t	i;
	size_t	size;

	size = get_token_count(str);
	tokens = malloc((size + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[size] = 0;
	i = 0;
	while (*str)
	{
		size = get_token_size(str);
		if (size > 0)
		{
			tokens[i] = malloc((size + 1) * sizeof(char));
			if (!tokens[i])
				return (clear_tokens(tokens, i - 1));
			ft_strlcpy(tokens[i], str, size + 1);
			++i;
		}
		str += size;
		proceed_to_next_token(&str);
	}
	return (tokens);
}
