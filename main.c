#include "get_next_line.h"

#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_num;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening file");
			return (1);
		}
	}
	else
		fd = 0; // Defaults to standard input (stdin) if no file is passed
	line_num = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d]: %s", line_num++, line);
		free(line);
	}
	if (argc == 2)
		close(fd);
	return (0);
}