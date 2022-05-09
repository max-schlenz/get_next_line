/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/05 08:35:01 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	static int		rcheck;
	char			*line = NULL;
	int				c_nl = 0;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rcheck > 0 && static_buffer[0] != '\0')
	{
		if (ft_find_n0(static_buffer) != -1)
				{
					line = ft_substr(static_buffer, 0, ft_find_n0(static_buffer), 1);
					static_buffer = ft_substr(static_buffer, ft_find_n0(static_buffer) + 1, ft_strlen(static_buffer) - ft_find_n0(static_buffer), 0);
					return (line);
				}
		line = ft_strdup(static_buffer);
	}
	
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rcheck] = '\0';
		c_nl = ft_find_n0(buffer);
		if (c_nl >= 0)
		{
			static_buffer = ft_substr(buffer, c_nl + 1, BUFFER_SIZE - c_nl, 0);
			buffer[c_nl] = '\n';
			buffer[c_nl + 1] = '\0';
			line = ft_strjoin(line, buffer);
			return (line);
		}
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>

int main(void) 
{
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = 0;
	//int fd = open("gnlTester/files/multiple_line_no_nl", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 9)
	{
	a = get_next_line(fd);
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
	i++;
	}
	system("leaks a.out");
}
