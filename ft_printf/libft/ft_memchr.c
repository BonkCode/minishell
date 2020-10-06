/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:17:46 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:20:11 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*array_pointer;

	array_pointer = (unsigned char *)s;
	if (!s)
		return (NULL);
	while (n > 0)
	{
		if (*array_pointer == (unsigned char)c)
			return (array_pointer);
		array_pointer++;
		n--;
	}
	return (NULL);
}
