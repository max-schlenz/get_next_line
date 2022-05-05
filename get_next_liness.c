/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/03 20:01:59 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		static_buffer[BUFFER_SIZE];
	static int		rcheck;
	char			*line;
	int				i = 0;
	static int		j;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(BUFFER_SIZE, 1);
	if (!line)
		return (NULL);
	if (rcheck > 0 && static_buffer[0] != '\0')
	{
		while (static_buffer[i] != '\0')
		{
			if (static_buffer[i] == '\n')
			{
				ft_strlcpy(line, static_buffer, i + 2);
				ft_strlcpy(static_buffer, &static_buffer[i + 1], (ft_strlen(static_buffer) - i));
				return (line);
			}
			i++;
		}	
		free(line);		
		line = ft_strdup(static_buffer);
		j = ft_strlen(line);
	}
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		buffer[BUFFER_SIZE] = '\0';
		while (i < rcheck)
		{
			if (buffer[i] == '\n')
			{
				ft_strlcpy(static_buffer, &buffer[i + 1], rcheck - i);
				line[j] = '\n';
				line[j + 1] = '\0';
				//line[j + 1] = '\0';
				j = ft_strlen(static_buffer);
				return(line);
			}
		line[j] = buffer[i];
		j++;
		i++;
		}
	}

	if (ft_strlen(line) > 0)
		return (line);
	else if (line)
			free(line);
		return (NULL);
}
/*
#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>

int main(void) 
{
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = 0;
	//int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
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
*/