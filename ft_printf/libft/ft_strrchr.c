/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:35:31 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:28:18 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurance_ptr;

	if (!s)
		return (NULL);
	last_occurance_ptr = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last_occurance_ptr = (char *)s;
		s++;
	}
	if (*s == (char)c)
		last_occurance_ptr = (char *)s;
	return (last_occurance_ptr);
}
