/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:03:37 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:59:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		free_chr(char **chr)
{
	if (chr && *chr)
	{
		free(*chr);
		*chr = NULL;
	}
}

char		*ft_find_lbreak(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (0);
}

size_t		ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char		*ft_strdup_gnl(char *str)
{
	char			*dest;
	char			*temp;

	temp = (char *)malloc(sizeof(*dest) * (ft_strlen_gnl(str) + 1));
	if (!temp)
		return (NULL);
	dest = temp;
	while (*str)
	{
		*temp = *str;
		temp++;
		str++;
	}
	*temp = '\0';
	return (dest);
}

char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*str;
	char		*res;
	size_t		len1;
	size_t		len2;

	if (!s1 && !s2)
		return (NULL);
	if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup_gnl(s2) : ft_strdup_gnl(s1));
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	res = str;
	while (*s1)
		*str++ = *s1++;
	free(s1 - len1);
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (res);
}
