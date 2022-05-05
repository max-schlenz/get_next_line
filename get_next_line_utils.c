/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschlenz <mschlenz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:35:24 by mschlenz          #+#    #+#             */
/*   Updated: 2022/05/05 21:24:17 by mschlenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	find_nl(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == '\n')
			return (i);
		i++;

	}
	return (-1);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t 	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s1);
	ptr = malloc(len + 1);
	if (!ptr)
		return (0);
	while (i <= len)
	{
	ptr[i] = s1[i];
	i++;
	}
	return (ptr);
}

char	*ft_strjoin_dup(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_s1s2;
	char	*str;

	i = 0;
	j = 0;
	len_s1s2 = 0;
	if (!s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	len_s1s2 = (ft_strlen(s1)) + (ft_strlen(s2));
	str = malloc(len_s1s2 + 1);
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_nl(char const *s, unsigned int start, size_t len, int flag)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	if (start >= (ft_strlen(s)))
	len = 0;
	if (len > (ft_strlen(s)))
		len = (ft_strlen(s));
	if (flag == 0)
		str = malloc(len + 1);
	else
		str = malloc(len + 2);
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	if (flag == 0)
		str[i] = '\0';
	else
		{
		str[i] = '\n';
		str[i + 1] = '\0';
		}
	return (str);
}
