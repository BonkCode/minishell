/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:41:11 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/09 17:08:40 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t c;
	size_t i;

	if (!*little)
		return ((char*)big);
	if (!big)
		return (NULL);
	c = 0;
	while (big[c] != '\0' && (size_t)c < len)
	{
		if (big[c] == little[0])
		{
			i = 1;
			while (little[i] != '\0' && big[c + i] == little[i] &&
			(c + i) < len)
				i++;
			if (little[i] == '\0')
				return ((char *)&big[c]);
		}
		c++;
	}
	return (0);
}
