/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/03 09:40:49 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	int				rcheck;
//	char			line_buf[BUFFER_SIZE + 1];
	char			*line_buf;
	int				nl_pos = 0;
	int				j = 0;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	//line = malloc(4096);
	
	// if (rcheck > 0 && static_buffer[0] != '\0')
	// {
	
	// }
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		//buffer[BUFFER_SIZE] = '\0';
		//printf("%d", nl_pos);
		nl_pos = ft_find_n0(buffer);
		if (nl_pos > 0)
		{
			//printf("%d", nl_pos);
			line_buf = ft_strdup
			line_buf = ft_strjoin(buffer, line_buf);
			//line_buf[rcheck] = '\0';
		}
		//printf("%s", buffer);
	}

	return (line_buf);
}

#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>

int main(void) 
{
	//int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = 0;
	//int fd = open("gnlTester/files/41_no_nl", O_RDONLY);
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
