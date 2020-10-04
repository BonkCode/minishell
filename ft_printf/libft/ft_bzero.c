/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 11:23:26 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/06 19:18:02 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*array_pointer;

	if (!s)
		return ;
	array_pointer = s;
	while (n > 0)
	{
		*array_pointer = '\0';
		array_pointer++;
		n--;
	}
}
