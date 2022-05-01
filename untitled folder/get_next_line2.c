/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:37:35 by mschlenz          #+#    #+#             */
/*   Updated: 2022/04/22 12:52:11 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char *buf[SIZE_BUF + 1];

	//buf = malloc(sizeof(char) * 9);
	read(fd, buf, SIZE_BUF);
	buf[8] = NULL;
	printf("%s", buf);
	return ("a");
}

int main(void) 
{
int fd = open("file.txt", O_RDWR | O_CREAT, 0777);
char *a = get_next_line(fd);
//char *buf = malloc(9);
//buf[9] = '\0';
//write(STDOUT_FILENO, buf, 9);
}

/*
int main(void) 
{
int fd = open("file.txt", O_RDWR | O_CREAT, 0777);
struct stat sb;
stat("file.txt", &sb);
char *buf = malloc(sb.st_size+1);
read(fd, buf, sb.st_size);
buf[sb.st_size] = '\0';
write(STDOUT_FILENO, buf, sb.st_size);
}
*/