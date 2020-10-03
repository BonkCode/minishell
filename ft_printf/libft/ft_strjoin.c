/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:45:04 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:40:45 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_str;
	unsigned int	i;
	unsigned int	new_str_len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	new_str_len = 0;
	while (s1[i++] != '\0')
		new_str_len++;
	i = 0;
	while (s2[i++] != '\0')
		new_str_len++;
	new_str = (char *)malloc((new_str_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	while (*s1 != '\0')
		new_str[++i] = *(s1++);
	while (*s2 != '\0')
		new_str[++i] = *(s2++);
	new_str[++i] = '\0';
	return (new_str);
}
