/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:14:51 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/12 14:11:44 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_2d(char **arr)
{
	int	i;

	if (!arr)
	{
		ft_printf("no array\n");
		return ;
	}
	i = -1;
	while (arr[++i])
		ft_printf("|%s| ", arr[i]);
}
