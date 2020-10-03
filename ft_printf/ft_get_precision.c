/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:52:17 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/05 20:02:38 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

int	get_precision(const char **format_string)
{
	int	precision;

	if (**format_string == '.')
	{
		++(*format_string);
		if (**format_string == '*')
		{
			++(*format_string);
			return (-2);
		}
		precision = ft_atoi(*format_string);
		while (ft_isdigit(**format_string))
			++(*format_string);
		return (precision);
	}
	return (-1);
}
