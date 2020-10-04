/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pointer_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:14:51 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/02 17:09:40 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static void	justify_return_string(t_directive *directive, char **return_string,
									char *number_to_print, size_t string_size)
{
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(*return_string, number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
		if (ft_strlen(number_to_print) != string_size)
			(*return_string)[ft_strlen(number_to_print)] = ' ';
	}
	else
	{
		ft_strlcpy(*return_string + string_size - ft_strlen(number_to_print),
		number_to_print,
		directive->precision > (int)ft_strlen(number_to_print) ?
		(size_t)directive->precision + 1 : string_size + 1);
	}
}

static void	free_strings(char **var_string, char **number_to_print)
{
	if (*var_string)
		free(*var_string);
	if (*number_to_print)
		free(*number_to_print);
}

char		*get_pointer_print(t_directive *directive,
			unsigned long int variable)
{
	size_t	string_size;
	char	*number_to_print;
	char	*return_string;
	char	*var_string;

	if (!(var_string = get_hex(variable, directive->conversion_character)))
		return (NULL);
	if (!(number_to_print = ft_strjoin("0x", var_string)))
	{
		free(var_string);
		return (NULL);
	}
	string_size = get_max(3, directive->field_width, directive->precision,
	ft_strlen(number_to_print));
	if (!(return_string = malloc((string_size + 1) * sizeof(char))))
	{
		free_strings(&var_string, &number_to_print);
		return (NULL);
	}
	return_string[string_size] = '\0';
	ft_memset(return_string, ' ', string_size);
	justify_return_string(directive, &return_string, number_to_print,
														string_size);
	free_strings(&var_string, &number_to_print);
	return (return_string);
}
