#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;
	int		line_num;


	fd = open("test.txt", O_RDONLY);

	line_num = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d]: %s", line_num++, line);
		free(line);
	}

	return (0);
}
