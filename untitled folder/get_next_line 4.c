/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:17:56 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/28 14:48:43 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (i >= dstsize || dstsize == 0)
		return (dstsize + ft_strlen(src));
	while (src[j] != '\0' && i < dstsize - 1)
	{
	dst[i] = ((char *)src)[j];
	i++;
	j++;
	}
	dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}

static size_t		print_static_buffer(char *buffer)
{
	//printf("%s", buffer);
	return (ft_strlen(buffer));
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	c_src;

	i = 0;
	c_src = 0;
	c_src = ft_strlen(src);
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	dst[i] = '\0';
	}
	return (c_src);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

int		search_char(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i - 1);
	i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	//size_t BUFFER_SIZE = 8;
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	static size_t	static_buffer_len;
	int				rcheck;
	char			*line;
	size_t	nl_char;

	char			*line_old;
	int				i;


	i = 0;
	rcheck = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(100);	
	line_old = malloc(100);	
//	if (static_buffer_len)
//	{
		//ft_strlcpy(line, static_buffer, static_buffer_len + 1);
		//printf("\ncp buf: %s\n", line);
//	}
	rcheck = (read(fd, buffer, BUFFER_SIZE));
	if (rcheck == 0 || rcheck == -1)
		return (NULL);

	nl_char = search_char(buffer, '\n');

	if (nl_char)
	{
		ft_strlcpy(line, buffer, (BUFFER_SIZE - nl_char));
		ft_strlcpy(line_old, buffer + nl_char + 1, (BUFFER_SIZE - nl_char));
	}
	//printf("\nline:%s\nline_old:%s\n", line, line_old);
	return (line);
}

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	//int fd = 0;
    int i = 0;
	char *a;

	while (i < 3)
	{
	a = get_next_line(fd);
		printf("%s\n", a);
	i++;
	}
}
