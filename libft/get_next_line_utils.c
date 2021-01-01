/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 13:09:51 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/01 23:09:15 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_str;
	unsigned int	i;
	unsigned int	new_str_len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	new_str_len = 0;
	while (s1[i++] != '\0')
		new_str_len++;
	i = 0;
	while (s2[i++] != '\0')
		new_str_len++;
	new_str = (char *)malloc((new_str_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	while (*s1 != '\0')
		new_str[++i] = *(s1++);
	while (*s2 != '\0')
		new_str[++i] = *(s2++);
	new_str[++i] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*s_copy;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	s_copy = (char *)malloc((s_len + 1) * sizeof(char));
	if (!s_copy)
		return (NULL);
	while (*s != '\0')
	{
		*s_copy = *s;
		s_copy++;
		s++;
	}
	*s_copy = '\0';
	return (s_copy - s_len);
}
