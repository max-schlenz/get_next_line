/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:05:37 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/06 15:04:21 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_string(int fd, char **buf_static)
{
	char	*buffer;
	char	*line;
	char	*tmp_line;
	int		rcheck;

	line = NULL;
	rcheck = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE));
	tmp_line = malloc(sizeof(char) * (BUFFER_SIZE));
	while (rcheck > 0)
	{
		rcheck = read(fd, buffer, BUFFER_SIZE);
		buffer[rcheck] = '\0';
		if (find_nl(buffer) >= 0)
		{
			*buf_static = ft_substr_nl(buffer, find_nl(buffer) + 1, \
									BUFFER_SIZE - find_nl(buffer), 0);
			tmp_line = ft_substr_nl(buffer, 0, find_nl(buffer), 1);
			line = ft_strjoin_dup(line, tmp_line);
			free (buffer);
			return (line);
		}
	line = ft_strjoin_dup(line, buffer);
	}
	if (buffer != NULL)
		free (buffer);
	if (rcheck == -1 || !line)
		return (NULL);
	return (line);
}

static char	*buf_static_split_nl(char **buf_static)
{	
	char	*temp;
	int		pos_nl;

	pos_nl = find_nl(*buf_static);
	temp = *buf_static;
	*buf_static = ft_substr_nl(*buf_static, pos_nl + 1, \
						ft_strlen(*buf_static) - pos_nl, 0);
	if (temp != NULL)
		free (temp);
	return (*buf_static);
}

char	*get_next_line(int fd)
{
	static char	*buf_static;
	char		*ptr_buf_static;
	char		*line;
	char		*line_tmp;

	line = NULL;
	line_tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf_static)
	{
		ptr_buf_static = buf_static;
		if (find_nl(buf_static) != -1)
		{
			line = ft_substr_nl(buf_static, 0, find_nl(buf_static), 1);
			buf_static = buf_static_split_nl(&buf_static);
			free (ptr_buf_static);
			return (line);
		}
		line_tmp = ft_strdup(buf_static);
		free (ptr_buf_static);
	}
	line = get_string(fd, &buf_static);
	line = ft_strjoin_dup(line_tmp, line);
	if (!line)
		return (NULL);
	if (ft_strlen(line) > 0)
		return (line);
	free (line);
	return (NULL);
}


#include "get_next_line_utils.c"
#include <fcntl.h>

int main(void) 
{
	//int fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/empty", O_RDONLY);
	//int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	int fd = open("gnlTester/files/41_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 9)
	{
	a = get_next_line(fd);
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
		free(a);
	i++;
	}
	system("leaks a.out");
}
