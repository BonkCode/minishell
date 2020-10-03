/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:51:37 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:22:14 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*array_pointer;

	array_pointer = s;
	if (!s)
		return (NULL);
	while (n > 0)
	{
		*array_pointer = c;
		array_pointer++;
		n--;
	}
	return (s);
}
