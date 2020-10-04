/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_int_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:14:15 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/02 17:12:55 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static char		*static_itoa(long long int n)
{
	long long int	n_copy;
	char			*res;
	int				size;

	n_copy = n;
	size = 1;
	while (ft_abs(n_copy) / ten_pow(size) > 0)
		size++;
	if (n_copy < 0)
		size++;
	if (!(res = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	res[size] = '\0';
	if (n_copy < 0)
		res[0] = '-';
	while (size-- > 0 && ft_abs(n_copy) >= 10)
	{
		res[size] = (ft_abs(n_copy) % 10) + '0';
		n_copy /= 10;
	}
	res[size] = (ft_abs(n_copy) % 10) + '0';
	return (res);
}

static char		*free_strings(char **zeroes, char **abs_var_string,
												char *return_string)
{
	if (*zeroes)
		free(*zeroes);
	if (*abs_var_string)
		free(*abs_var_string);
	return (return_string);
}

static char		*setup_return_string(t_directive *directive,
									long long int variable,
									size_t *string_size, char **number_to_print)
{
	int		zeroes_count;
	char	*zeroes;
	char	*return_string;
	char	*abs_var_string;

	abs_var_string = static_itoa(ft_abs(variable));
	zeroes_count = directive->precision -
		ft_strlen(abs_var_string);
	zeroes = zeroes_count >= 0 ? ft_calloc(zeroes_count + 1, sizeof(char)) :
	ft_strdup("");
	ft_memset(zeroes, '0', zeroes_count >= 0 ? zeroes_count : 0);
	if (directive->conversion_character == '%')
		*number_to_print = ft_strjoin(zeroes, "%");
	else
		*number_to_print = ft_strjoin(zeroes, variable == 0 &&
			directive->precision == 0 ? "" : abs_var_string);
	*string_size = get_max(3, directive->field_width, directive->precision,
												ft_strlen(*number_to_print));
	return_string = malloc((*string_size + 1) * sizeof(char));
	return_string[*string_size] = '\0';
	ft_memset(return_string, (ft_strchr(directive->flags, '0') &&
		directive->precision < 0) ||
	directive->precision > (int)ft_strlen(*number_to_print) ? '0' :
													' ', *string_size);
	return (free_strings(&zeroes, &abs_var_string, return_string));
}

static void		justify_return_string(t_directive *directive,
									char **return_string,
									char *number_to_print, size_t string_size)
{
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(*return_string, number_to_print,
		directive->precision > (int)ft_strlen(number_to_print) ?
		(size_t)directive->precision + 1 : string_size + 1);
		if (ft_strlen(number_to_print) != string_size)
			(*return_string)[ft_strlen(number_to_print)] =
			ft_strchr(directive->flags, '0') || directive->precision >
			(int)ft_strlen(number_to_print) ? '0' : ' ';
	}
	else
	{
		ft_strlcpy(*return_string + string_size - ft_strlen(number_to_print),
		number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
	}
}

char			*get_int_print(t_directive *directive, long long int variable)
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
	if (variable < 0)
		return_string = i_add_minus_sign(directive, return_string, ptr_to_free);
	else if (ft_strchr(directive->flags, ' ') ||
			ft_strchr(directive->flags, '+'))
		return_string = i_add_plus_or_space(directive, variable, return_string,
			ptr_to_free);
	free(number_to_print);
	return (return_string);
}
