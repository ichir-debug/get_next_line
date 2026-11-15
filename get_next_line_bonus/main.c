#include "get_next_line_bonus.h"

#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;
	int		line_num;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	fd3 = open("file3.txt", O_RDONLY);

	printf("%s", get_next_line_bonus(fd1));
	printf("%s", get_next_line_bonus(fd2));
	printf("%s", get_next_line_bonus(fd3));
	printf("%s", get_next_line_bonus(fd3));
	printf("%s", get_next_line_bonus(fd1));
	printf("%s", get_next_line_bonus(fd2));
	printf("%s", get_next_line_bonus(fd1));
	printf("%s", get_next_line_bonus(fd3));
	printf("%s", get_next_line_bonus(fd2));

	return (0);
}
