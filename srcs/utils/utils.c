/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 19:06:30 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 19:54:23 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"

void					sigint_skip(int c)
{
	write(1, "\n", 1);
}

void					del(void *data)
{
	if (data)
		free(data);
	data = NULL;
}

int						str_is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

char					*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*str;
	char		*res;
	size_t		len1;
	size_t		len2;

	if (!s1 && !s2)
		return (NULL);
	if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	res = str;
	while (*s1)
		*str++ = *s1++;
	free(s1 - len1);
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (res);
}
