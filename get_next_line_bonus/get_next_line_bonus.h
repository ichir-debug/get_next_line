#ifndef GET_NEXT_LINE_BONUS
#define GET_NEXT_LINE_BONUS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

size_t      ft_strlen(const char *s);
size_t	    ft_strlcpy(char *dest, const char *src, size_t size);
char	    *ft_strdup(const char *s);
char	    *ft_strjoin(char const *s1, char const *s2);

char        *get_next_line_bonus(int fd);
char	    *ft_extract_line(char **stash);
char	    *ft_fill_stash(int fd, char *stash);
int	        is_line_finished(char *buff, int ret);

#endif