/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/10 17:11:49 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	create_line(char **line, char **stat_buf, int fd, int rcheck)
{
	char			buf[BUFFER_SIZE + 1];
	char			*temp;
	char			*temp2;

	temp = NULL;
	temp2 = NULL;
	while (rcheck > 0)
	{
		rcheck = read(fd, buf, BUFFER_SIZE);
		buf[rcheck] = '\0';
		temp = *line;
		if (p_nl(buf) >= 0)
		{
			*stat_buf = substr(buf, p_nl(buf) + 1, BUFFER_SIZE - p_nl(buf), 1);
			temp2 = substr(buf, 0, p_nl(buf), 2);
			*line = ft_strjoin_dup(*line, temp2);
			free(temp2);
			if (temp != NULL)
				free(temp);
			break ;
		}
		*line = ft_strjoin_dup(*line, buf);
		free(temp);
	}
	return (rcheck);
}

static void	split_stat_buf(char **stat_buf)
{
	int	stat_buf_nl;

	stat_buf_nl = p_nl(*stat_buf);
	*stat_buf = substr(*stat_buf, stat_buf_nl + 1, \
				ft_strlen(*stat_buf) - stat_buf_nl, 1);
}

static char	*check_return(char *line)
{
	if (!line)
		return (NULL);
	if (ft_strlen(line) > 0)
		return (line);
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*stat_buf = NULL;
	char			*line;
	char			*temp;

	line = NULL;
	temp = NULL;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stat_buf)
	{
		if (p_nl(stat_buf) != -1)
		{
			temp = stat_buf;
			line = substr(stat_buf, 0, p_nl(stat_buf), 2);
			split_stat_buf(&stat_buf);
			free (temp);
			return (line);
		}
		line = ft_strdup(stat_buf);
		free (stat_buf);
		stat_buf = NULL;
	}
	create_line(&line, &stat_buf, fd, 1);
	line = check_return(line);
	return (line);
}
/*
#include "get_next_line_utils.c"
#include <fcntl.h>

int main(void) 
{
	//int fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/nl", O_RDONLY);
	int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	//int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/empty", O_RDONLY);
	//int fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 3)
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