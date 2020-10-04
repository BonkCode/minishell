/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:35:58 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/08 16:18:25 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long	local_abs(long n)
{
	return (n < 0 ? -n : n);
}

static long	ten_pow(int size)
{
	long	res;

	res = 1;
	if (size <= 0)
		return (1);
	while (size-- > 0)
		res *= 10;
	return (res);
}

char		*ft_itoa(int n)
{
	long	n_copy;
	char	*res;
	int		size;

	n_copy = n;
	size = 1;
	while (local_abs(n_copy) / ten_pow(size) > 0)
		size++;
	if (n_copy < 0)
		size++;
	if (!(res = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	res[size] = '\0';
	if (n_copy < 0)
		res[0] = '-';
	while (size-- > 0 && local_abs(n_copy) >= 10)
	{
		res[size] = (local_abs(n_copy) % 10) + '0';
		n_copy /= 10;
	}
	res[size] = (local_abs(n_copy) % 10) + '0';
	return (res);
}
