/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 02:25:20 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:59:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_get_size(int n)
{
	int		size;
	long	tmp;

	tmp = n;
	size = 1;
	if (tmp < 0)
	{
		size++;
		tmp = -tmp;
	}
	while (tmp >= 10)
	{
		size++;
		tmp /= 10;
	}
	return (size);
}

char		*ft_itoa(int nb)
{
	char			*str;
	long			nbr;
	int				i;
	int				len;

	i = 0;
	len = ft_get_size(nb);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (nb < 0)
		str[0] = '-';
	nbr = nb;
	if (nbr < 0)
		nbr = -nbr;
	str[len - i++] = '\0';
	while (nbr >= 10)
	{
		str[len - i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len - i++] = (nbr % 10) + '0';
	return (str);
}
