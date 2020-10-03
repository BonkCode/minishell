/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_add_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:09:10 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/06 06:16:07 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

char			*i_add_minus_sign(t_directive *directive,
								char *str, char *ptr_to_free)
{
	if (!ft_strchr(directive->flags, '-'))
	{
		if (directive->precision < directive->field_width &&
			ft_strchr(str, ' '))
			*(ft_strrchr(str, ' ')) = '-';
		else if (*str == '0' && directive->precision < 0)
			*str = '-';
		else
		{
			ptr_to_free = str;
			str = ft_strjoin("-", ptr_to_free);
			free(ptr_to_free);
		}
	}
	else if (((str[0] == '0' && directive->precision < 0) || str[0] == ' '))
		str[0] = '-';
	else
	{
		if (ft_strrchr(str, ' '))
			*(ft_strrchr(str, ' ')) = '\0';
		ptr_to_free = str;
		str = ft_strjoin("-", ptr_to_free);
		free(ptr_to_free);
	}
	return (str);
}

static void		i_join_sign(t_directive *directive, char **return_string,
						char *ptr_to_free)
{
	ptr_to_free = *return_string;
	*return_string = ft_strjoin(ft_strchr(directive->flags, '+') ?
		"+" : " ", ptr_to_free);
	free(ptr_to_free);
}

char			*i_add_plus_or_space(t_directive *directive, double variable,
								char *str, char *ptr_to_free)
{
	if (!ft_strchr(directive->flags, '-'))
	{
		if (directive->precision < directive->field_width &&
			ft_strchr(str, ' '))
			*(ft_strrchr(str, ' ')) =
				ft_strchr(directive->flags, '+') ? '+' : ' ';
		else if (*str == '0' && directive->precision <=
			directive->field_width && (variable != 0 ||
				ft_strrchr(str, '0') != str))
			*str = ft_strchr(directive->flags, '+') ? '+' : ' ';
		else
			i_join_sign(directive, &str, ptr_to_free);
	}
	else if (((str[0] == '0' && directive->precision < 0) ||
		str[0] == ' ') && (variable != 0 ||
			ft_strrchr(str, '0') != str))
		str[0] = ft_strchr(directive->flags, '+') ? '+' : ' ';
	else
	{
		if (ft_strrchr(str, ' '))
			*(ft_strrchr(str, ' ')) = '\0';
		i_join_sign(directive, &str, ptr_to_free);
	}
	return (str);
}
