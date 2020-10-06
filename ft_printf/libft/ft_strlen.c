/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:01:59 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:26:04 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	str_len;

	if (!s)
		return (0);
	str_len = 0;
	while (*s != '\0')
	{
		str_len++;
		s++;
	}
	return (str_len);
}
