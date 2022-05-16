/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/12 14:05:31 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	create_line(char **line, char **stat_buf, int fd, int rcheck)
{
	char			buf[BUFFER_SIZE + 1];
	char			*ptr_old_line;
	char			*buf_substr_nl;

	ptr_old_line = NULL;
	buf_substr_nl = NULL;
	while (rcheck > 0)
	{
		rcheck = read(fd, buf, BUFFER_SIZE);
		buf[rcheck] = '\0';
		ptr_old_line = *line;
		if (p_nl(buf) >= 0)
		{
			*stat_buf = substr(buf, p_nl(buf) + 1, BUFFER_SIZE - p_nl(buf), 1);
			buf_substr_nl = substr(buf, 0, p_nl(buf), 2);
			*line = ft_strjoin_dup(*line, buf_substr_nl);
			free (buf_substr_nl);
			if (ptr_old_line != NULL)
				free (ptr_old_line);
			break ;
		}
		*line = ft_strjoin_dup(*line, buf);
		free(ptr_old_line);
	}
}

static void	trim_stat_buf(char **stat_buf)
{
	int		stat_buf_nl;
	char	*ptr_stat_buf;

	stat_buf_nl = p_nl(*stat_buf);
	ptr_stat_buf = *stat_buf;
	*stat_buf = substr(*stat_buf, stat_buf_nl + 1, \
				ft_strlen(*stat_buf) - stat_buf_nl, 1);
	free (ptr_stat_buf);
}

char	*get_next_line(int fd)
{
	static char		*stat_buf[4096];
	char			*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stat_buf[fd])
	{
		if (p_nl(stat_buf[fd]) == -1)
			line = ft_strdup(stat_buf[fd]);
		else
		{
			line = substr(stat_buf[fd], 0, p_nl(stat_buf[fd]), 2);
			trim_stat_buf(&stat_buf[fd]);
			return (line);
		}
		free (stat_buf[fd]);
		stat_buf[fd] = NULL;
	}
	create_line(&line, &stat_buf[fd], fd, 1);
	if (ft_strlen(line) > 0)
		return (line);
	free (line);
	return (NULL);
}

/*
#include "get_next_line_utils.c"
#include <fcntl.h>

int main(void) 
{
	//int fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/nl", O_RDONLY);
	//int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/empty", O_RDONLY);
	//int fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 7)
	{
	a = get_next_line(fd);
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
		free(a);
	i++;
	}
//system("leaks a.out");
}
*/