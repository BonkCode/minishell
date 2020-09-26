/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:55:37 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:59:09 by rtrant           ###   ########.fr       */
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
			(size_t)(c + i) < len)
				i++;
			if (little[i] == '\0')
				return ((char*)&big[c]);
		}
		c++;
	}
	return (0);
}
