/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:25:08 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/05 12:19:53 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buffer; //[BUFFER_SIZE + 1];
	static char		*static_buffer;
	char			*line = NULL;
	char			*line_tmp;
	static int		rcheck;
	int				pos_nl;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	pos_nl = 0;
	if (line)
		free (line);
	if (rcheck > 0 && static_buffer)
	{
		pos_nl = find_nl(static_buffer);
		if (pos_nl != -1)
		{
			line = ft_substr_nl(static_buffer, 0, pos_nl, 1);
			static_buffer = ft_substr_nl(static_buffer, ft_strlen(line), (ft_strlen(static_buffer) - (ft_strlen(line))), 0);
			return (line);
		}
		line = ft_strdup(static_buffer);
		free (static_buffer);
	}
	buffer = malloc((sizeof(char) * BUFFER_SIZE + 1));
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) != 0)// && (ft_strchr(static_buffer, '\n')))
	{
			if (rcheck == -1)
			{
				free (buffer);
				return (NULL);
			}
			buffer[rcheck] = '\0';
			if (ft_strchr(buffer, '\n'))
			{
				//static_buffer = ft_strjoin_dup(static_buffer, line);
				pos_nl = find_nl(buffer);
				static_buffer = ft_substr_nl(buffer, pos_nl + 1, BUFFER_SIZE - pos_nl, 0);
				line_tmp = ft_substr_nl(buffer, 0, pos_nl, 1);
				line = ft_strjoin_dup(line, line_tmp);
				free (line_tmp);
				return (line);
			}
			line = ft_strjoin_dup(line, buffer);
			//line = ft_strdup(buffer);
	}
	free (buffer);
	if (!line)
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
