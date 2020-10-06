/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:49:51 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/06 08:33:13 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static void	get_flag(const char flag_character, char **flags, int *i)
{
	if (flag_character == '-')
	{
		if (!ft_strchr(*flags, '-') && !ft_strchr(*flags, '0'))
			(*flags)[++(*i)] = flag_character;
		else if (ft_strchr(*flags, '0'))
			*(ft_strchr(*flags, '0')) = flag_character;
	}
	if (flag_character == '0' && !ft_strchr(*flags, '0') &&
		!ft_strchr(*flags, '-'))
		(*flags)[++(*i)] = flag_character;
	if (flag_character == ' ' && !ft_strchr(*flags, ' ') &&
		!ft_strchr(*flags, '+'))
		(*flags)[++(*i)] = flag_character;
	if (flag_character == '+')
	{
		if (!ft_strchr(*flags, '+' && !ft_strchr(*flags, ' ')))
			(*flags)[++(*i)] = flag_character;
		else if (ft_strchr(*flags, ' '))
			*(ft_strchr(*flags, ' ')) = flag_character;
	}
	if (flag_character == '#')
		(*flags)[++(*i)] = flag_character;
}

char		*get_flags(const char **format_string)
{
	int		i;
	char	*format_characters;
	char	*flags;

	if (!(format_characters = ft_strdup("-+ 0#")))
		return (NULL);
	i = -1;
	if (!(flags = ft_calloc(4, sizeof(char))))
		return (NULL);
	while (ft_strchr(format_characters, **format_string))
	{
		get_flag(**format_string, &flags, &i);
		++(*format_string);
	}
	free(format_characters);
	return (flags);
}
