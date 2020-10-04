/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:45:47 by rtrant            #+#    #+#             */
/*   Updated: 2020/10/03 17:03:38 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_elem;

	ft_putstr_fd("qqq\n", 1);
	if (!del)
		return ;
	while ((*lst) != NULL)
	{
		ft_putstr_fd("qqq\n", 1);
		next_elem = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_elem;
	}
}
