/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 11:43:49 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:22:56 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_pointer;
	const unsigned char	*src_pointer;

	if (!dest || !src)
		return (dest);
	dest_pointer = dest;
	src_pointer = src;
	while (n > 0)
	{
		*dest_pointer = *src_pointer;
		dest_pointer++;
		src_pointer++;
		n--;
	}
	return (dest);
}
