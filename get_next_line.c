/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/01 22:29:15 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		static_buffer[BUFFER_SIZE];
	static int		rcheck;
	char			*line;
	int				i = 0;
	static int		j = 0;
	static int		memm;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(4096, 1);
	if (!line)
		return (NULL);
	if (rcheck > 0 && static_buffer[0] != '\0')
	{
		while (static_buffer[i] != '\0')
			{
				if (static_buffer[i] == '\n')
				{
					line[j] = '\n';
					ft_strlcpy(static_buffer, &static_buffer[i + 1], (ft_strlen(static_buffer)) - i);
					return (line);
				}
				line[j] = static_buffer[i];
				i++;
				j++;
			}
	}
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		memm++;
		while (i < rcheck)
		{	
			if (buffer[i] == '\n')
			{
				line[j] = '\n';
				ft_strlcpy(static_buffer, &buffer[i + 1], rcheck - i);
				return (line);
			}
			line[j] = buffer[i];
			i++;
			j++;
		}
	}
	if (ft_strlen(line) > 0)
		return (line);
	else if (line)
			free(line);
		return (NULL);
}

#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>

int main(void) 
{
	//int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = 0;
	int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 1)
	{
	a = get_next_line(fd);
	if (a)
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
	i++;
	}
	//system("leaks a.out");
}