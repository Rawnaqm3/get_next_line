#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

    i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(s1) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof (*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		ptr[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[j] = s2[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
    free (s1);
	return (ptr);
} 

char	*ft_before_newline(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1[i])
		return (NULL);
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		str[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
    free(s1);
	return (str);
} 

char	*ft_after_newline(char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
    if (!s2[i])
	{
		free(s2);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s2) - i + 1));
	if (!str)
		return (NULL);
	while (s2[i] && s2[i] != '\n')
		i++;
	if (s2[i] == '\n')
		i++;
	j = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_read(int fd, char *s1)
{
	char	*buff;
	int		rd_bytes;
    // char    *temp;

    buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
        // temp = s1;
		s1 = ft_strjoin(s1, buff);
        // free(temp);
		if (ft_strchr(s1, '\n') != NULL)
			break ;
	}
    if(buff)
	    free(buff);
	return (s1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s1;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (0);
	s1 = ft_read(fd, s1);
	if (!s1)
		return (NULL);
	line = ft_before_newline(s1);
	s1 = ft_after_newline(s1);
	return (line);
}

// int main()
// {
// 	int fd;

// 	fd = open("file.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
// 	close (fd);
// 	return(0);
// }

// int main(void)
// {
//     char *a = "hello \nworld";

//     printf("%s", ft_after_newline(a));
//     return (0);
// }