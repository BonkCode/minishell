/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:56:39 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:59:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*dst_dst;
	unsigned char		*src_src;

	dst_dst = (unsigned char*)dst;
	src_src = (unsigned char*)src;
	i = 0;
	if (!src && !dst)
		return (NULL);
	while (i < n)
	{
		dst_dst[i] = src_src[i];
		if (src_src[i] == (unsigned char)c)
			return (dst + i + 1);
		else
			i++;
	}
	return (NULL);
}
