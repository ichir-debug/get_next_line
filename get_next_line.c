#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *stash;
    static int file_size;
    static int offset;
    char *res;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    res = "";
    if(stash)
    {
        res = ft_empty_stash(&stash);
        if(!res)
            return NULL;
    }
    stash = ft_fill_stash(fd, &offset);
    if(!stash)
        return NULL;
    if(offset == file_size)
        return NULL;
    file_size = offset;
    res = ft_strjoin(res, ft_empty_stash(&stash));
    if(!res)
        return NULL;
    return (res);
}
