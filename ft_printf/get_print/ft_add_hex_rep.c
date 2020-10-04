/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_hex_rep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 06:41:26 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/06 07:22:27 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static void	append_hex_rep(char *ptr_to_free, char **str,
						t_directive *directive)
{
	ptr_to_free = *str;
	**str = directive->conversion_character;
	*str = ft_strjoin("0", ptr_to_free);
	free(ptr_to_free);
}

char		*add_hex_rep_ljust(t_directive *directive,
								char *str, char *ptr_to_free)
{
	if (directive->precision < directive->field_width &&
		ft_strchr(str, ' '))
	{
		if (ft_strrchr(str, ' ') == str)
			append_hex_rep(ptr_to_free, &str, directive);
		else
			ft_memcpy(ft_strrchr(str, ' ') - 1,
				directive->conversion_character == 'x' ? "0x" : "0X", 2);
	}
	else if (*str == '0' && directive->precision < 0)
	{
		if (*(str + 1) == '0')
			ft_memcpy(str, directive->conversion_character == 'x'
				? "0x" : "0X", 2);
		else
			append_hex_rep(ptr_to_free, &str, directive);
	}
	else
	{
		ptr_to_free = str;
		str = ft_strjoin(directive->conversion_character == 'x' ?
			"0x" : "0X", ptr_to_free);
		free(ptr_to_free);
	}
	return (str);
}

char		*add_hex_rep_rjust(t_directive *directive,
								char *str, char *ptr_to_free)
{
	if ((str[0] == '0' && str[1] == '0' &&
		directive->precision < 0) || (str[0] == ' ' &&
		str[1] == ' '))
		ft_memcpy(str, directive->conversion_character == 'x' ?
			"0x" : "0X", 2);
	else if ((str[0] == '0' && directive->precision < 0) ||
		str[0] == ' ')
		append_hex_rep(ptr_to_free, &str, directive);
	else
	{
		if (ft_strrchr(str, ' '))
		{
			if (*(ft_strrchr(str, ' ') - 1) == ' ')
				*(ft_strrchr(str, ' ') - 1) = '\0';
			else
				*(ft_strrchr(str, ' ')) = '\0';
		}
		ptr_to_free = str;
		str = ft_strjoin(directive->conversion_character == 'x' ?
			"0x" : "0X", ptr_to_free);
		free(ptr_to_free);
	}
	return (str);
}
