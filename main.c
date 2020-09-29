#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char *line;
	int fd;

	fd = open("main.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	ft_putstr_fd(line, 1);
	ft_putstr_fd("\n", 1);
	printf("%zu\n", ft_strlen(line));
	return (0);
}
