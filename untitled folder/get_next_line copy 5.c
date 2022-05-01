/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:51:17 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/30 16:12:16 by mschlenz         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc((ft_strlen(s1)) + (ft_strlen(s2)) + 1);
	if (!str)
		return (0);
	while (i < (ft_strlen(s1)))
	{
		str[i] = s1[i];
		i++;
	}
	while (i < ((ft_strlen(s1)) + (ft_strlen(s2))))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		len_s1;
	int		i;
	char	*ptr;

	len_s1 = ft_strlen(s1);
	i = 0;
	ptr = malloc(len_s1 + 1);
	if (!ptr)
		return (0);
	while (i <= len_s1)
	{
	ptr[i] = s1[i];
	i++;
	}
	return (ptr);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		static_buffer[BUFFER_SIZE];
	int				rcheck;
	char			*line;
	int				i = 0;
	size_t			j = 0;

	rcheck = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1024);
	if (!line)
		return (NULL);
	if (static_buffer[0] != '\0')
		{
		ft_strlcpy(line, static_buffer, (ft_strlen(static_buffer) + 1));
		j = ft_strlen(static_buffer);
		}
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{			
		while (i < rcheck && buffer[i] != '\n')
		{
			line[j] = buffer[i];
			i++;
			j++;
		}
		if (buffer[i] == '\n')
		{
			ft_strlcpy(static_buffer, buffer + i + 1, (BUFFER_SIZE - (search_char(buffer, '\n'))));
			break ;
		}
		i = 0;
	}
	if (ft_strlen(line) > 0)
	{
		//line[(ft_strlen(line))] = '\n';
		return (line);
	}
	else
	{
		if (line)
			free(line);
		//return (ft_strdup("\n"));
		return (NULL);
	}
}

int main(void)
{
	int fd = open("alternate_line_nl_no_nl", O_RDONLY);
	//int fd = 0;
    int i = 0;
	char *a;

	while (i < 5)
	{
	a = get_next_line(fd);
	i++;
	}
	printf("%s", a);
}
