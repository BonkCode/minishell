/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_conversion_character.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:53:21 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/14 15:57:19 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

char	get_conversion_character(const char **format_string)
{
	char	conversion_character;

	if (ft_strchr("cspdiuxX%", **format_string) && **format_string != '\0')
	{
		conversion_character = **format_string;
		++(*format_string);
		return (conversion_character);
	}
	++(*format_string);
	return (ERROR);
}
