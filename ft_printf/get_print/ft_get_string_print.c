/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:13:09 by rtrant            #+#    #+#             */
/*   Updated: 2020/07/02 17:04:54 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static char	*free_var_if_needed(char **variable, int null_flag,
											char *return_string)
{
	if (null_flag && *variable)
		free(*variable);
	return (return_string);
}

static char	*get_return_string(t_directive *directive, char *variable,
														int null_flag)
{
	size_t	var_len;
	size_t	string_size;
	char	*return_string;

	var_len = (size_t)get_min(2, ft_strlen(variable), directive->precision >= 0
		? (size_t)directive->precision : ft_strlen(variable));
	string_size = get_max(2, directive->field_width, var_len);
	if (!(return_string = malloc((string_size + 1) * sizeof(char))))
		return (free_var_if_needed(&variable, null_flag, return_string));
	return_string[string_size] = '\0';
	ft_memset(return_string, ' ', string_size);
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(return_string, variable, directive->precision >= 0 ?
		(size_t)directive->precision + 1 : string_size + 1);
		if (var_len != string_size)
			return_string[var_len] = ' ';
	}
	else
		ft_strlcpy(return_string + string_size - var_len, variable,
		var_len + 1);
	return (return_string);
}

char		*get_string_print(t_directive *directive, char *variable)
{
	char	*return_string;
	int		null_flag;

	null_flag = 0;
	if (variable == NULL)
	{
		null_flag = 1;
		if (!(variable = ft_strdup("(null)")))
			return (NULL);
	}
	return_string = get_return_string(directive, variable, null_flag);
	return (free_var_if_needed(&variable, null_flag, return_string));
}
