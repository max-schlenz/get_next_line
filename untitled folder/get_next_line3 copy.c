/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:51:17 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/01 18:13:56 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		static_buffer[4096];
	static int		rcheck;
	char			*line;
	int				i = 0;
	int				j = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(4096);
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
					//line[ft_strlen(line)] = '\0';
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
		while (i < rcheck)
		{	
			if (buffer[i] == '\n')
			{
				line[j] = '\n';
				ft_strlcpy(static_buffer, &buffer[i + 1], rcheck - i);
				//line[ft_strlen(line)] = '\0';
				return (line);
			}
			line[j] = buffer[i];
			i++;
			j++;
		}
	}
	if (ft_strlen(line) > 0)		//line[ft_strlen(line)] = '\0';
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
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = 0;
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	a = get_next_line(fd);
	while (a != NULL)
	{
		// if (i > 10)
		// 	printf("| %d:%s",i + 1, a);
		//printf("%s", a);
		if (i < 11)
		{
			printf("|%d:%s",i + 1, a);
			//printf("%s", a);
		}
		//free(a);
		a = get_next_line(fd);
		i++;
	}
	printf("\n|%d:%s",i + 1, a);
	//system("leaks a.out");

	/*while (i < 9)
	{
	a = get_next_line(fd);
	if (a)
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
	i++;
	}
	while (i < 11)
	{
	a = get_next_line(fd);
	if (a)
		printf("|%d:%s",i + 1, a);
		//printf("%s", a);
	i++;
	}*/
}
