/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy 9.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/08 14:18:31 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*split_stat_buf(char *static_buffer)
{	
	char	*temp;
	int		pos_nl;

	temp = NULL;
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

	temp = NULL;
	temp2 = NULL;
	pos_nl = find_nl(buffer);
	temp2 = ft_substr_nl(buffer, 0, pos_nl, 1);
	temp = line;
	line = ft_strjoin_dup(line, temp2);
	if (temp != NULL)
		free(temp);
	if (temp2 != NULL)
		free(temp2);
	return (line);
}

char	*check_return(char *line)
{
	if (!line)
		return (NULL);
	if (ft_strlen(line) > 0)
		return (line);
	free(line);
	return (NULL);
}

static char	*create_return_line(int fd, char **static_buffer)
{
	char	*temp;
	char 	*line;
	char 	*tmp2;
	char	buffer[BUFFER_SIZE + 1];
	int		rcheck;

	line = NULL;
	temp = NULL;
	tmp2 = NULL;
	rcheck = 1;
	while (rcheck > 0)
	{
		rcheck = read(fd, buffer, BUFFER_SIZE);
		buffer[rcheck] = '\0';
		if (find_nl(buffer) >= 0)
		{
			*static_buffer = ft_substr_nl(buffer, find_nl(buffer) + 1, \
					BUFFER_SIZE - find_nl(buffer), 0);
			line = create_line(line, buffer);
			return (line);
		}
		temp = line;
		line = ft_strjoin_dup(line, buffer);
		if (temp != NULL)
			free(temp);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*static_buffer;
	char			*line;
	char			*line2;
	char			*tmp1;

	line = NULL;
	line2 = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (static_buffer)
	{
		if (find_nl(static_buffer) != -1)
		{
			line = ft_substr_nl(static_buffer, 0, find_nl(static_buffer), 1);
			static_buffer = split_stat_buf(static_buffer);
			return (line);
		}
		line = ft_strdup(static_buffer);
		static_buffer = NULL;
	}
	line2 = create_return_line(fd, &static_buffer);
	tmp1 = line;
	line = ft_strjoin_dup(line, line2);
	if (tmp1 != NULL)
		free (tmp1);
	line = check_return(line);
	return (line);
}

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
