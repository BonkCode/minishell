/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:58:32 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/08 16:19:02 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	new_len;

	if (!s1)
		return (NULL);
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	new_len = ft_strlen(s1);
	while (s1[new_len - 1] != '\0' && ft_strchr(set, s1[new_len - 1]) != NULL
	&& new_len > 0)
		new_len--;
	new_str = (char *)malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, new_len + 1);
	return (new_str);
}
