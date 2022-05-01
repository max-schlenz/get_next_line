/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:51:17 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/28 16:31:09 by mschlenz         ###   ########.fr       */
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
			return (i);
	i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		static_buffer[BUFFER_SIZE + 1];
	int				rcheck;
	char			*line;
	int				i = 0;

	rcheck = 0;
	line = malloc(1024);
	//static_buffer = malloc(1024);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//if (static_buffer[0] != '\0')
		printf("%s", static_buffer);
	while ((rcheck = (read(fd, buffer, BUFFER_SIZE))) >= 0) // && (!ft_strchr(buffer, '\n')))
	{
		while (i < rcheck && buffer[i] != '\n' && buffer[i] != '\0')
		{
			line[i] = buffer[i];
			i++;
		}
		if (buffer[i] == '\n')
		{
			ft_strlcpy(static_buffer, buffer + i + 1, (BUFFER_SIZE - search_char(buffer, '\n')));
			//static_buffer[(ft_strlen(static_buffer)) + 1] = '\0';
			break ;
			
		}
		i = 0;
		if (rcheck == 0)
		{
			break ;
		}
	}
	
	//line[rcheck] = '\0';
	return (line);
}

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	//int fd = 0;
    int i = 0;
	char *a;

	while (i < 5)
	{
	a = get_next_line(fd);
		printf("%s\n", a);
	i++;
	}
}
