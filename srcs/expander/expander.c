/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:44:50 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/10 17:01:32 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "m_types.h"
#include "flexer.h"

int			expand(char ***tokens, t_list *env)
{
	int		i;

	if (!tokens || !env)
		return (1);
	i = -1;
	while ((*tokens)[++i])
	{
		expand_token(&(*tokens)[i], env);
	}
	return (0);
}
