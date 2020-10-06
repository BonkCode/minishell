/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_length_modifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:52:41 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/06 08:35:27 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

char	*get_length_modifier(const char **format_string)
{
	int		i;
	char	*length_modifier;

	i = -1;
	if (!(length_modifier = ft_calloc(3, sizeof(char))))
		return (NULL);
	while (ft_strchr("hl", **format_string))
	{
		if (ft_strchr(length_modifier, **format_string))
		{
			length_modifier[++i] = **format_string;
			++(*format_string);
			break ;
		}
		length_modifier[++i] = **format_string;
		++(*format_string);
	}
	return (length_modifier);
}
