/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:15:24 by rtrant            #+#    #+#             */
/*   Updated: 2020/09/08 13:59:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_line(char **list_fd, char **line, char *p_lbrake)
{
	char *tmp;

	*p_lbrake = '\0';
	p_lbrake++;
	*line = ft_strdup_gnl(*list_fd);
	if (!*line)
		return (-1);
	if (*p_lbrake == '\0')
	{
		free_chr(list_fd);
		return (1);
	}
	tmp = ft_strdup_gnl(p_lbrake);
	free(*list_fd);
	*list_fd = tmp;
	return (1);
}

static int		get_from_storage(char **list_fd, char **line,
int read_size, char **buff)
{
	char *p_lbrake;

	free_chr(buff);
	if (read_size < 0)
		return (-1);
	if (*list_fd && (p_lbrake = ft_find_lbreak(*list_fd)))
		return (get_line(list_fd, line, p_lbrake));
	if (*list_fd)
	{
		*line = *list_fd;
		*list_fd = NULL;
		return (0);
	}
	*line = ft_strdup_gnl("");
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*list_fd[FDS];
	char		*buff;
	int			read_size;
	char		*p_lbrake;

	buff = NULL;
	if (!line || fd < 0 || fd > FDS || read(fd, buff, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (BUFFER_SIZE > 2147483646 || !(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((read_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_size] = '\0';
		if (!(list_fd[fd] = ft_strjoin_gnl(list_fd[fd], buff)))
		{
			free_chr(&buff);
			return (-1);
		}
		if ((p_lbrake = ft_find_lbreak(list_fd[fd])))
		{
			free_chr(&buff);
			return (get_line(&list_fd[fd], line, p_lbrake));
		}
	}
	return (get_from_storage(&list_fd[fd], line, read_size, &buff));
}
