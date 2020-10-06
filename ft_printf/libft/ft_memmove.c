/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:02:27 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:22:38 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_pointer;
	const unsigned char	*src_pointer;
	size_t				i;

	dest_pointer = dest;
	src_pointer = src;
	if (!dest || !src)
		return (dest);
	i = 0;
	if (src_pointer < dest_pointer)
	{
		while (++i <= n)
			dest_pointer[n - i] = src_pointer[n - i];
	}
	else
	{
		while (n-- > 0)
			*(dest_pointer++) = *(src_pointer++);
	}
	return (dest);
}
