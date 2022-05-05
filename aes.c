	char			*buffer;
	static char		*static_buffer;
	char			*line;
	char			*temp;
	static int		rcheck;
	int				pos_nl;
	
	pos_nl = 0;
	line = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rcheck > 0 && static_buffer)
	{
		pos_nl = find_nl(static_buffer);
		if (pos_nl != -1)
		{
			line = ft_substr_nl(static_buffer, 0, pos_nl, 1);
			static_buffer = split_stat_buf(static_buffer);
			return (line);
		}
		line = ft_strdup(static_buffer);
		free (static_buffer);
	}
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while ((rcheck > 0)
	{
		rcheck = read(fd, buffer, BUFFER_SIZE);
		buffer[rcheck] = '\0';
		pos_nl = find_nl(buffer);
		if (pos_nl >= 0)
		{
			static_buffer = ft_substr_nl(buffer, pos_nl + 1, \
					BUFFER_SIZE - pos_nl, 0);
			line = create_line(line, buffer);
			return (line);
		}
		temp = line;
		line = ft_strjoin_dup(line, buffer);
		if (temp != NULL)
			free(temp);
	}
	if (buffer != NULL)
		free (buffer);
	if (rcheck == -1 || !line)
		return (NULL);
	if (ft_strlen(line) > 0)
		return (line);
	free (line);
	return (NULL);