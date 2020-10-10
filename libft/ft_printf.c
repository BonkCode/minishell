/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 06:52:18 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/14 15:57:49 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"
#include "libftprintf.h"

static int	free_directive(t_directive **directive)
{
	if (!(*directive))
		return (0);
	if ((*directive)->length_modifier)
		free((*directive)->length_modifier);
	if ((*directive)->flags)
		free((*directive)->flags);
	free(*directive);
	return (0);
}

char		*get_what_to_print(va_list argptr, t_directive *directive)
{
	if (directive->conversion_character == 'c')
		return (get_char_print(directive, va_arg(argptr, int)));
	else if (directive->conversion_character == 's')
		return (get_string_print(directive, va_arg(argptr, char *)));
	else if (ft_strchr("uxX", directive->conversion_character))
		return (choose_u_int_print_variant(directive, argptr));
	else if (ft_strchr("di", directive->conversion_character))
		return (choose_int_print_variant(directive, argptr));
	else if (directive->conversion_character == '%')
		return (get_int_print(directive, '%'));
	else if (directive->conversion_character == 'p')
		return (get_pointer_print(directive,
		va_arg(argptr, unsigned long int)));
	else
		return (ft_strdup(""));
}

static int	manage_star_flag(t_directive **dir, va_list argptr)
{
	char	*copy;

	if ((*dir)->field_width == -2)
	{
		(*dir)->field_width = va_arg(argptr, int);
		if ((*dir)->field_width < 0)
		{
			copy = (*dir)->flags;
			if (ft_strchr((*dir)->flags, '0'))
				*(ft_strchr((*dir)->flags, '0')) = '-';
			else
			{
				if (copy)
					free(copy);
				if (!((*dir)->flags = ft_strjoin((*dir)->flags, "-")))
					return (free_directive(dir));
			}
		}
		(*dir)->field_width = ft_abs((*dir)->field_width);
	}
	if ((*dir)->precision == -2)
		(*dir)->precision = va_arg(argptr, int);
	return (1);
}

static int	print_formatted(const char **format_string, va_list argptr)
{
	t_directive	*directive;
	char		*what_to_print;
	int			return_value;

	directive = get_directive(format_string);
	if (directive == NULL)
		return (0);
	if (!manage_star_flag(&directive, argptr))
		return (0);
	if (!(what_to_print = get_what_to_print(argptr, directive)))
		return (free_directive(&directive));
	ft_putstr_fd(what_to_print, 1);
	if (directive->conversion_character == 'c' &&
		ft_strlen(what_to_print) == 0)
		return_value = directive->field_width > 0 ?
						directive->field_width : 1;
	else
		return_value = ft_strlen(what_to_print);
	if (what_to_print)
		free(what_to_print);
	free_directive(&directive);
	return (return_value);
}

int			ft_printf(const char *format_string, ...)
{
	va_list		argptr;
	int			return_value;

	return_value = 0;
	va_start(argptr, format_string);
	while (*format_string != '\0')
	{
		if (*format_string == '%')
			return_value += print_formatted(&format_string, argptr);
		else
		{
			ft_putchar_fd(*format_string, 1);
			++return_value;
			++format_string;
		}
	}
	va_end(argptr);
	return (return_value);
}
