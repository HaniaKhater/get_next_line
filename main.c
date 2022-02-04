#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int		fd_1;
	int		fd_2;
	char	*line;

	fd_1 = open("test.txt", O_RDONLY);
	fd_2 = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd_1)) != NULL)
	{
		printf("[%s]\n", line);
		free (line);
	}
	printf("[%s]", line);
	close(fd_1);
	close(fd_2);
	free(line);
}