/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_variants.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:21:49 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/02 16:30:42 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include <stdarg.h>

char	*choose_int_print_variant(t_directive *directive, va_list argptr)
{
	if (ft_strchr(directive->length_modifier, 'l'))
	{
		if (ft_strlen(directive->length_modifier) == 1)
			return (get_int_print(directive, va_arg(argptr,
			long int)));
		else
			return (get_int_print(directive, va_arg(argptr,
			long long int)));
	}
	return (get_int_print(directive, va_arg(argptr, int)));
}

char	*choose_u_int_print_variant(t_directive *directive, va_list argptr)
{
	if (ft_strchr(directive->length_modifier, 'l'))
	{
		if (ft_strlen(directive->length_modifier) == 1)
			return (get_unsigned_int_print(directive, va_arg(argptr,
			unsigned long int)));
		else
			return (get_unsigned_int_print(directive, va_arg(argptr,
			unsigned long long int)));
	}
	return (get_unsigned_int_print(directive, va_arg(argptr,
	unsigned int)));
}
