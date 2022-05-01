/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:05:28 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/27 19:06:02 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*static_buffer;
	static size_t	static_buffer_len;
	int				rcheck;
	char			*line;

	char			*line_old;
	int				i;


	i = 0;
	rcheck = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(100);	
	if (static_buffer_len)
	{
		ft_strlcpy(line, static_buffer, static_buffer_len + 1);
		//printf("\ncp buf: %s\n", line);
	}
	rcheck = (read(fd, buffer, BUFFER_SIZE));
	if (rcheck == 0 || rcheck == -1)
		return (NULL);
	
	size_t	nl_char;

	nl_char = search_char(buffer, '\n');

//	ft_strlcat(line, buffer, (BUFFER_SIZE - static_buffer_len));
	if (!static_buffer_len)
		ft_strlcpy(line, buffer, BUFFER_SIZE - nl_char + 1);
	else
		ft_strlcat(line, buffer, (1 + BUFFER_SIZE - ft_strlen(static_buffer)));
	//printf("\ncat: %s\n", line);
	if (BUFFER_SIZE >= nl_char)
	{
		static_buffer = malloc(100);
		ft_strlcpy(static_buffer, buffer + nl_char + 1, (BUFFER_SIZE - nl_char));
		//ft_strlcpy(static_buffer, buffer + nl_char, (BUFFER_SIZE - nl_char + 1));
		//printf("\nSTATIC_BUFFER:%s\n", static_buffer);
		static_buffer_len = ft_strlen(static_buffer);
	}
	//printf("\n STATIC BUF:%s\n", static_buffer);
	return (line);
}

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	//int fd = 0;
    int i = 0;
	char *a;

	while (i < 3)
	{
	a = get_next_line(fd);
		printf("%s\n", a);
	i++;
	}
}
