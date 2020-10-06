/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_field_width.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:51:05 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/05 20:02:26 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

int	get_field_width(const char **format_string)
{
	int	field_width;

	if ((field_width = ft_atoi(*format_string)) && field_width > 0)
	{
		while (ft_isdigit(**format_string))
			++(*format_string);
		return (field_width);
	}
	else if (**format_string == '*')
	{
		++(*format_string);
		return (-2);
	}
	return (-1);
}
