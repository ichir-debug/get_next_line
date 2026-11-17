/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irichi <irichi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:12:56 by irichi            #+#    #+#             */
/*   Updated: 2026/11/17 21:16:24 by irichi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*r1(char *s1, char **s2)
{
	free (s1);
	if (s2)
		*s2 = NULL;
	return (NULL);
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
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *stash, i + 1);
	remaining = ft_strdup(*stash + i);
	if (!remaining)
		return (r1(line, NULL));
	free(*stash);
	*stash = remaining;
	if (!(*stash)[0])
		r1(*stash, stash);
	return (line);
}

char	*ft_fill_stash(int fd, char *stash, size_t buffer_size)
{
	char	*buff;
	char	*temp;
	int		ret;

	buff = (char *)malloc(buffer_size + 1);
	if (!buff)
		return (r1(stash, NULL));
	ret = 1;
	while (!is_line_finished(stash, ret))
	{
		ret = read(fd, buff, buffer_size);
		if (ret < 0)
		{
			r1(stash, NULL);
			return (r1(buff, NULL));
		}
		buff[ret] = '\0';
		temp = ft_strjoin(stash, buff);
		free(stash);
		stash = temp;
		if (!stash)
			return (r1(buff, NULL));
	}
	free(buff);
	return (stash);
}

char	*get_next_line_bonus(int fd)
{
	static char	*stash[1024];
	char		*line;
	size_t		buffer_size;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_size = BUFFER_SIZE;
	if (!stash[fd])
	{
		stash[fd] = ft_strdup("");
		if (!stash[fd])
			return (NULL);
	}
	stash[fd] = ft_fill_stash(fd, stash[fd], buffer_size);
	if (!stash[fd])
		return (NULL);
	if (!(*stash[fd]))
		return (r1(stash[fd], &stash[fd]));
	line = ft_extract_line(&(stash[fd]));
	if (!line)
		return (r1(stash[fd], &stash[fd]));
	return (line);
}
