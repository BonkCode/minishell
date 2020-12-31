/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:53:57 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/31 19:26:20 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*copy_till_char(char *str, char c)
{
	int		size;
	char	*return_string;

	size = 0;
	while (str[size] && str[size] != c)
		++size;
	if (!(return_string = ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	ft_strlcpy(return_string, str, size + 1);
	return (return_string);
}
