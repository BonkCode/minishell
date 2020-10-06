/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unsigned_int_print.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvernius <rvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:13:41 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/06 12:52:30 by rvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*ft_uitoa(unsigned long long int n)
{
	unsigned long long int	n_copy;
	char					*res;
	int						size;

	n_copy = n;
	size = 1;
	while (n_copy / ten_pow(size) > 0)
		size++;
	if (!(res = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	res[size] = '\0';
	while (size-- > 0 && n_copy >= 10)
	{
		res[size] = (n_copy % 10) + '0';
		n_copy /= 10;
	}
	res[size] = (n_copy % 10) + '0';
	return (res);
}

static void	justify_return_string(t_directive *directive, char **return_string,
									char *number_to_print, size_t string_size)
{
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(*return_string, number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
		if (ft_strlen(number_to_print) != string_size)
			(*return_string)[ft_strlen(number_to_print)] =
			ft_strchr(directive->flags,
			'0') || directive->precision > (int)ft_strlen(number_to_print) ?
			'0' : ' ';
	}
	else
	{
		ft_strlcpy(*return_string + string_size - ft_strlen(number_to_print),
		number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
	}
}

static char	*setup_return_string(t_directive *directive,
									long long int variable,
									size_t *string_size, char **number_to_print)
{
	int		zeroes_count;
	char	*zeroes;
	char	*return_string;
	char	*var_string;

	var_string = directive->conversion_character == 'u' ? ft_uitoa(variable) :
		get_hex(variable, directive->conversion_character);
	zeroes_count = directive->precision - ft_strlen(var_string);
	zeroes = zeroes_count >= 0 ? ft_calloc(zeroes_count + 1, sizeof(char)) :
	ft_strdup("");
	ft_memset(zeroes, '0', zeroes_count >= 0 ? zeroes_count : 0);
	if (directive->precision == 0 && variable == 0)
		*number_to_print = ft_strjoin(zeroes, "");
	else
		*number_to_print = ft_strjoin(zeroes, var_string);
	*string_size = get_max(3, directive->field_width, directive->precision,
	ft_strlen(*number_to_print));
	return_string = malloc((*string_size + 1) * sizeof(char));
	return_string[*string_size] = '\0';
	ft_memset(return_string, (ft_strchr(directive->flags, '0') &&
		directive->precision < 0) || directive->precision >
		(int)ft_strlen(*number_to_print) ? '0' : ' ', *string_size);
	free(var_string);
	free(zeroes);
	return (return_string);
}

char		*get_unsigned_int_print(t_directive *directive,
									unsigned long long int variable)
{
	size_t	string_size;
	char	*number_to_print;
	char	*return_string;
	char	*ptr_to_free;

	return_string = setup_return_string(directive, variable, &string_size,
		&number_to_print);
	justify_return_string(directive, &return_string, number_to_print,
	string_size);
	ptr_to_free = return_string;
	if (variable != 0 && ft_strchr("xX", directive->conversion_character) &&
		ft_strchr(directive->flags, '#') && !ft_strchr(directive->flags, '-'))
		return_string = add_hex_rep_ljust(directive, return_string,
			ptr_to_free);
	else if (variable != 0 && ft_strchr("xX",
		directive->conversion_character) && ft_strchr(directive->flags, '#'))
		return_string = add_hex_rep_rjust(directive, return_string,
			ptr_to_free);
	free(number_to_print);
	return (return_string);
}
