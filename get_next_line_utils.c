#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

int is_line_finished(char *buff, int ret)
{
    if(ret == 0)
        return 1;
    while(*buff)
    {
        if(*buff == '\n')
           return 1; 
        buff++;
    }
    return 0;
}

char* ft_empty_stash(char **stash)
{
    char *res;
    size_t len;
    size_t i;

    len = 0;
    while((*stash)[len])
    {
        len++;
        if((*stash)[len] == '\n')
        {
            len++;
            break;
        }
    }
    res = malloc(sizeof(char) * (len + 1));
    if(!res)
        return NULL;
    i = 0;
    while(i < len)
    {
        res[i] = *(*stash)++;
        i++;
    }
    res[i] = '\0';
    return (res);
}

char *ft_fill_stash(int fd, int *offset)
{
    char *stash;
    char *buff;
    char *temp;
    int ret;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if(!buff)
        return (NULL);
    stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if(!stash)
        return (NULL);
    stash[0] = '\0';
    ret = 1;
    while(!is_line_finished(buff, ret))
    {
        ret = read(fd, buff, BUFFER_SIZE);
        if(ret == -1)
            return NULL;
        *offset += ret;
        buff[ret] = '\0';
        temp = stash;
        stash = ft_strjoin(temp, buff);
        free(temp);
    }
    free(buff);
    return(stash);
}
