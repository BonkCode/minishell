/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 01:22:50 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/12 01:35:46 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main(int argc, char **argv, char **environ)
{
	for (int i = 0; i < argc; ++i)
	{
		printf("%s\n", argv[i]);
	}
	return (1);
}
