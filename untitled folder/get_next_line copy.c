/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:36:37 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/26 18:10:49 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
    char			buf[BUFFER_SIZE + 1];
    //unsigned int	len = BUFFER_SIZE;
	int				rcheck = 0;
    int				i = 0;
	int				j = 0;
	static char		tmp_char[BUFFER_SIZE + 1];
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    rcheck = (read(fd, buf, BUFFER_SIZE));
	if (rcheck == 0 || rcheck == -1)
		return (NULL);
	ret=malloc(BUFFER_SIZE);
	if (!ret)
		return (NULL);
    buf[BUFFER_SIZE] = '\0';
	while (tmp_char[i] != '\0')
	{
		ret[j] = tmp_char[i];
		i++;
		j++;
	}
	i = 0;
    while (i < BUFFER_SIZE)
    {
		while (buf[i] != '\n' && buf[i] != '\0')
		{
        ret[j] = buf[i];
		i++;
		j++;
		}
		j = 0;
		while (buf[i] != '\0')
		{
			tmp_char[j] = buf[i];
			i++;
			j++;
		}
        i++;
    }
	ret[BUFFER_SIZE - 1] = '\0';
	tmp_char[j] = '\0';
	return (ret);
}

/*
int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    int i = 0;
	char *a;
	
	while (i < 5)
	{
	a = get_next_line(fd);
		printf("%s", a);
	i++;
	}
}
*/