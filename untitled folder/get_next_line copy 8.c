/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/06 16:08:23 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*split_stat_buf(char *static_buffer)
{	
	char	*temp;
	int		pos_nl;

	pos_nl = find_nl(static_buffer);
	temp = static_buffer;
	static_buffer = ft_substr_nl(static_buffer, pos_nl + 1, \
						ft_strlen(static_buffer) - pos_nl, 0);
	if (temp != NULL)
		free (temp);
	return (static_buffer);
}

char	*create_line(char *line, char *buffer)
{
	char	*temp;
	char	*temp2;
	int		pos_nl;

	pos_nl = find_nl(buffer);
	temp2 = (ft_substr_nl(buffer, 0, pos_nl, 1));
	temp = line;
	line = ft_strjoin_dup(line, temp2);
	if (temp != NULL)
		free(temp);
	if (temp2 != NULL)
		free(temp2);
	return (line);
}

char	*check_return(char *line, int rcheck)
{
	if (rcheck == -1 || !line)
		return (NULL);
	if (ft_strlen(line) > 0)
		return (line);
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	char			*line;
	char			*temp;
	char			*temp2;
	static int		rcheck;

	line = NULL;
	temp = NULL;	
	temp2 = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rcheck > 0 && static_buffer)
	{
		if (find_nl(static_buffer) != -1)
		{
			line = ft_substr_nl(static_buffer, 0, find_nl(static_buffer), 1);
			static_buffer = split_stat_buf(static_buffer);
			return (line);
		}
		line = ft_strdup(static_buffer);
		free (static_buffer);
	}
	rcheck = 1;
	while (rcheck > 0)
	{
		rcheck = read(fd, buffer, BUFFER_SIZE);
		buffer[rcheck] = '\0';
		if (find_nl(buffer) >= 0)
		{
			static_buffer = ft_substr_nl(buffer, find_nl(buffer) + 1, \
					BUFFER_SIZE - find_nl(buffer), 0);
			line = create_line(line, buffer);
			return (line);
		}
		temp = line;
		line = ft_strjoin_dup(line, buffer);
		if (temp != NULL)
			free(temp);
	}
	line = check_return(line, rcheck);
	return (line);
}
/*
#include "get_next_line_utils.c"
#include <fcntl.h>

int main(void) 
{
	//int fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/empty", O_RDONLY);
	//int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
	//int fd = open("gnlTester/files/41_no_nl", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 10)
	{
	a = get_next_line(fd);
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
		free(a);
	i++;
	}
	system("leaks a.out");
}
*/