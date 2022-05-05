/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 21:00:32 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/05 20:57:20 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	char			*line;
	char			*temp;
	char			*temp2;
	static int		rcheck;
	int				pos_nl;
	
	pos_nl = 0;
	line = NULL;
	temp = NULL;
	temp2 = NULL;
	//printf("\nSTATIC BUF: %s\n", static_buffer);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rcheck > 0 && static_buffer)
	{
		pos_nl = find_nl(static_buffer);
		if (pos_nl != -1)
		{
			temp = static_buffer;
			line = ft_substr_nl(static_buffer, 0, pos_nl, 1);
			static_buffer = ft_substr_nl(static_buffer, pos_nl + 1, ft_strlen(static_buffer) - pos_nl, 0);
			if (temp != NULL)
				free (temp);
			return (line);
		}
		line = ft_strdup(static_buffer);
		free (static_buffer);
	}
	while ((rcheck = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rcheck] = '\0';
		pos_nl = find_nl(buffer);
		temp = line;
		if (pos_nl >= 0)
		{
			static_buffer = ft_substr_nl(buffer, pos_nl + 1, BUFFER_SIZE - pos_nl, 0);
			temp2 = (ft_substr_nl(buffer, 0, pos_nl, 1));
			line = ft_strjoin_dup(line, temp2);
			if (temp != NULL)
				free(temp);
			if (temp2 != NULL)
				free(temp2);
			return (line);
		}
		line = ft_strjoin_dup(line, buffer);
		if (temp != NULL)
			free(temp);
	}
	
	if (rcheck == -1 || !line)
		return (NULL);
	else 
		{
		if (ft_strlen(line) > 0)
			return (line);
		free (line);
		return (NULL);
		}
}


#include "get_next_line_utils.c"
#include <fcntl.h>

int main(void) 
{
	//int fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/nl", O_RDONLY);
	//int fd = open("gnlTester/files/41_with_nl", O_RDONLY);
	int fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	//int fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	//int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;

	while (i < 6)
	{
	a = get_next_line(fd);
		printf("| %d:%s",i + 1, a);
		//printf("%s", a);
		free(a);
	i++;
	}
	//system("leaks a.out");
}
