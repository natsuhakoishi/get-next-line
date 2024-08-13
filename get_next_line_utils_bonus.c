/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa <yyean-wa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:37:24 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/11/15 14:37:46 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	int		a;
	int		b;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	b = 0;
	while (s2[b] != '\0')
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	if ((unsigned char)c == 0)
		return ((char *)(str + ft_strlen(str)));
	while (*str)
	{
		if (*str == (unsigned char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (0);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	len;

	if (size > 0 && n > UINT_MAX / size)
		return (0);
	len = n * size;
	ptr = malloc(len);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, len);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*str++ != '\0')
		a++;
	return (a);
}

void	*ft_memset(void *b, int c, size_t size)
{
	size_t			a;
	unsigned char	*str;

	a = 0;
	str = b;
	while (a < size)
	{
		*str++ = (unsigned char)c;
		a++;
	}
	return (b);
}
