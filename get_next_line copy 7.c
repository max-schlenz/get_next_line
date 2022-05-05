/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/05 13:41:52 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	char			*line;
	static int		rcheck;
	int				pos_nl;
	static int		ttt;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	pos_nl = 0;
	line = NULL;
	if (rcheck > 0 && static_buffer)
	{
		pos_nl = find_nl(static_buffer);
		if (pos_nl != -1)
		{
			line = ft_substr_nl(static_buffer, 0, pos_nl, 1);
			static_buffer = ft_substr_nl(static_buffer, pos_nl + 1, ft_strlen(static_buffer) - pos_nl, 0);
			return (line);
		}
		line = ft_strdup(static_buffer);
		free (static_buffer);
	}
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rcheck] = '\0';
		pos_nl = find_nl(buffer);
		if (pos_nl >= 0)
		{
			static_buffer = ft_substr_nl(buffer, pos_nl + 1, BUFFER_SIZE - pos_nl, 0);
			line = ft_strjoin_dup(line, (ft_substr_nl(buffer, 0, pos_nl, 1)));
			return (line);
		}
		line = ft_strjoin_dup(line, buffer);
	}
	if (rcheck == -1 || !line)
		return (NULL);
	else
		return (line);
}

#include "get_next_line_utils.c"
#include <stdio.h>
#include <fcntl.h>

int main(void) 
{
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/41_no_nl", O_RDONLY);
	//int fd = 0;
	//int fd = open("gnlTester/files/multiple_line_no_nl", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 10)
	{
	a = get_next_line(fd);
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
	i++;
	}
//	system("leaks a.out");
}
