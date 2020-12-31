/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:47:42 by rtrant            #+#    #+#             */
/*   Updated: 2020/12/31 19:27:24 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flexer.h"

void	free_2_str(char **s1, char **s2)
{
	if (*s1)
		free(*s1);
	*s1 = NULL;
	if (*s2)
		free(*s2);
	*s2 = NULL;
}

void	*clear_3d(char ****arr, int n, int k)
{
	int	i;
	int	j;

	if (!(*arr))
		return (NULL);
	i = -1;
	while ((*arr)[++i] && (i < n || n < 0))
	{
		j = -1;
		while ((*arr)[i][++j] && (j < k || k < 0))
		{
			free((*arr)[i][j]);
			(*arr)[i][j] = NULL;
		}
		free((*arr)[i]);
		(*arr)[i] = NULL;
	}
	free((*arr));
	(*arr) = NULL;
	return (NULL);
}
