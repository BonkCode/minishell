/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 13:08:27 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/03 20:43:33 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif
# include <unistd.h>
# include <stdlib.h>
# define MAX_FD_COUNT 512

int		get_next_line(int fd, char **line);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		get_next_line_no_eof(int fd, char **line);

#endif
