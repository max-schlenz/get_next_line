/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:35:24 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/01 20:47:21 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_find_n0(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\n' && c[i] != '\0')
		i++;
	//if (i == 0 && c[0] != '\n' && c[0] != '\0')
	//	i = -1;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	c_src;

	i = 0;
	c_src = 0;
	c_src = ft_strlen(src);
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	dst[i] = '\0';
	}
	return (c_src);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc((ft_strlen(s1)) + (ft_strlen(s2)) + 1);
	if (!str)
		return (0);
	while (i < (ft_strlen(s1)))
	{
		str[i] = s1[i];
		i++;
	}
	while (i < ((ft_strlen(s1)) + (ft_strlen(s2))))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
	((char *)s)[i] = '\0';
	i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && 18446744073709551615UL / size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (i >= dstsize || dstsize == 0)
		return (dstsize + ft_strlen(src));
	while (src[j] != '\0' && i < dstsize - 1)
	{
	dst[i] = ((char *)src)[j];
	i++;
	j++;
	}
	dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}
