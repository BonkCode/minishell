/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:15:09 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:38:10 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	current_size;
	size_t	full_size;

	if (!dst || !src)
		return (size);
	full_size = ft_strlen(src) + ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	current_size = ft_strlen(dst);
	while (*dst != '\0')
		dst++;
	while (current_size < size - 1 && *src != '\0')
	{
		*dst = *src;
		src++;
		dst++;
		current_size++;
	}
	*dst = '\0';
	return (full_size);
}
