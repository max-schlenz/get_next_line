/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:36:37 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/27 14:20:52 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../libft/ft_strchr.c"

char	*get_next_line(int fd)
{
    char			buf[BUFFER_SIZE + 1];
    //unsigned int	len = BUFFER_SIZE;
	int				rcheck = 0;
    int				i = 0;
	int				j = 0;
	static char		tmp_char[BUFFER_SIZE + 1];
	static size_t	tmp_char_len;
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret=malloc(tmp_char_len + (ft_strchr('')) + 1);
	while (tmp_char[i] != '\0')
	{
		ret[j] = tmp_char[i];
		i++;
		j++;
	}
    rcheck = (read(fd, buf, BUFFER_SIZE));
	if (rcheck == 0 || rcheck == -1)
		return (NULL);
	if (!ret)
		return (NULL);
    //buf[BUFFER_SIZE] = '\0';
    while (i < BUFFER_SIZE)
    {
		while (buf[i] != '\0' && i < rcheck)
		{
			ret[j] = buf[i];
			i++;
			j++;
		}
		ret[j] = '\0';
		j = 0;
		while (buf[i] != '\0')
		{
			tmp_char[j] = buf[i];
			i++;
			j++;
		}
        i++;
    }
	tmp_char_len = j;
	//tmp_char[j] = '\0';
	return (ret);
}

/*
int main(void)
{
	//int fd = open("file.txt", O_RDONLY);
	int fd = 0;
    int i = 0;
	char *a;
	
	while (i < 6)
	{
	a = get_next_line(fd);
		printf("%s", a);
	i++;
	}
}
*/