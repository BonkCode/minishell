/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:08:52 by rtrant            #+#    #+#             */
/*   Updated: 2020/11/27 07:31:35 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define FDS 14000
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t			ft_strlen_gnl(const char *s);
char			*ft_find_lbreak(char *s);
void			free_chr(char **chr);
char			*ft_strdup_gnl(char *str);
char			*ft_strjoin_gnl(char *s1, char *s2);
#endif
