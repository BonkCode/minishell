/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 13:09:48 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/01 23:05:47 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_line_eof(char **line, char **remainder)
{
	*line = ft_strdup(*remainder);
	free(*remainder);
	*remainder = NULL;
	if (!(*line))
		return (-1);
	return (0);
}

static int	get_line(char **eol, char **line, char **remainder)
{
	char	*ptr_to_free;

	*eol = *eol ? *eol : ft_strchr(*remainder, '\n');
	if (*eol != NULL)
	{
		**eol = '\0';
		if (!(*line = ft_strdup(*remainder)))
		{
			free(*remainder);
			*remainder = NULL;
			return (-1);
		}
		ptr_to_free = *remainder;
		if (((*eol)[1] != '\0' && !((*remainder) = ft_strdup(*eol + 1))) ||
			(*eol)[1] == '\0')
			*remainder = NULL;
		free(ptr_to_free);
		return (1);
	}
	return (get_line_eof(line, remainder));
}

static int	get_status(char **eol, char **line, char **remainder, int readed)
{
	if (readed < 0)
		return (-1);
	else if (readed == 0 && (!(*remainder) || (*remainder)[0] == '\0'))
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	return (get_line(eol, line, remainder));
}

int			get_next_line(int fd, char **line)
{
	static char	*remainder[MAX_FD_COUNT];
	char		*ptr_to_free;
	char		*eol;
	int			readed;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE < 1 || fd > MAX_FD_COUNT)
		return (-1);
	eol = remainder[fd] ? ft_strchr(remainder[fd], '\n') : NULL;
	readed = 0;
	while (!eol && (readed = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[readed] = '\0';
		if (!remainder[fd] && (!(remainder[fd] = ft_strdup(""))))
			return (-1);
		ptr_to_free = remainder[fd];
		remainder[fd] = ft_strjoin(remainder[fd], buffer);
		free(ptr_to_free);
		if (!remainder[fd])
			return (-1);
		eol = ft_strchr(remainder[fd], '\n');
	}
	return (get_status(&eol, line, &remainder[fd], readed));
}
