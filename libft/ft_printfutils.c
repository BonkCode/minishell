/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:10:34 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/06 08:36:34 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"
#include "libft.h"

int				get_max(int count, ...)
{
	int		max;
	int		current_number;
	va_list	argptr;

	va_start(argptr, count);
	max = va_arg(argptr, int);
	while (--count > 0)
	{
		current_number = va_arg(argptr, int);
		if (max < current_number)
			max = current_number;
	}
	va_end(argptr);
	return (max);
}

int				get_min(int count, ...)
{
	int		min;
	int		current_number;
	va_list	argptr;

	va_start(argptr, count);
	min = va_arg(argptr, int);
	while (--count > 0)
	{
		current_number = va_arg(argptr, int);
		if (min > current_number)
			min = current_number;
	}
	va_end(argptr);
	return (min);
}

long long int	ten_pow(int size)
{
	long long int	res;

	res = 1;
	if (size <= 0)
		return (1);
	while (size-- > 0)
		res *= 10;
	return (res);
}

char			*get_hex(unsigned long long int variable,
						char conversion_character)
{
	char					*result;
	int						size;
	unsigned long long int	variable_copy;

	variable_copy = variable;
	size = 0;
	while (variable_copy > 0)
	{
		variable_copy /= 16;
		++size;
	}
	if (!(result = ft_calloc((size + 1), sizeof(int))))
		return (NULL);
	while (variable > 0)
	{
		if (conversion_character == 'X')
			result[--size] = variable % 16 < 10 ? variable % 16 + '0' :
			variable % 16 % 10 + 'A';
		else
			result[--size] = variable % 16 < 10 ? variable % 16 + '0' :
			variable % 16 % 10 + 'a';
		variable /= 16;
	}
	result[0] = result[0] == '\0' ? '0' : result[0];
	return (result);
}

long long int	ft_abs(long int n)
{
	return (n < 0 ? -n : n);
}
