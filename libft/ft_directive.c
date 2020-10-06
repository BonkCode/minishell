/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_directive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:08:55 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 12:40:52 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_directive	*get_directive(const char **format_string)
{
	t_directive	*directive;

	++(*format_string);
	if (!(directive = (t_directive *)malloc(sizeof(t_directive))))
		return (NULL);
	if (!(directive->flags = get_flags(format_string)))
		return (NULL);
	if (**format_string == '\0')
		return (NULL);
	directive->field_width = get_field_width(format_string);
	if (**format_string == '\0')
		return (NULL);
	directive->precision = get_precision(format_string);
	if (**format_string == '\0')
		return (NULL);
	if (**format_string == '\0')
		return (NULL);
	if (!(directive->length_modifier = get_length_modifier(format_string)))
		return (NULL);
	if (**format_string == '\0')
		return (NULL);
	directive->conversion_character = get_conversion_character(format_string);
	return (directive);
}
