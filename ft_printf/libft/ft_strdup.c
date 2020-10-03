/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:10:38 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:24:56 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
