#include "get_next_line.h"

int	is_line_finished(char *buff, int ret)
{
	int	i;

	if (ret == 0)
		return (1);
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_extract_line(char **stash)
{
	char	*line;
	char	*remaining;
	size_t	i;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *stash, i + 1);
	remaining = ft_strdup(*stash + i);
	free(*stash);
	*stash = remaining;
	return (line);
}

char	*ft_fill_stash(int fd, char *stash)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ret = 1;
	while (!is_line_finished(stash, ret))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (free(buff), NULL);
		buff[ret] = '\0';

		temp = ft_strjoin(stash, buff);
		free(stash);
		stash = temp;
		if (!stash)
			return (free(buff), NULL);
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = ft_fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	if (!*stash)
		return (free(stash), stash = NULL, NULL);
	line = ft_extract_line(&stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	return (line);
}
