/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 23:38:39 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:59:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*dst;
	size_t			i;

	dst = (char *)malloc(sizeof(*dst) * (ft_strlen(str) + 1));
	if (dst == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (str[i])
		{
			dst[i] = str[i];
			i++;
		}
		dst[i] = '\0';
		return (dst);
	}
}
