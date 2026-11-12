#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char        *get_next_line(int fd);
char        *ft_fill_stash(int fd, int *offset);
char        *ft_empty_stash(char **stash);
char	    *ft_strjoin(char const *s1, char const *s2);
size_t      ft_strlen(const char *s);

#endif