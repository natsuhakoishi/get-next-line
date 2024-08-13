/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa <yyean-wa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:19:02 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/11/15 15:03:00 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinfree(char *buf1, char *buf2)
{
	char	*bufree;

	bufree = ft_strjoin(buf1, buf2);
	if (buf1)
		free(buf1);
	return (bufree);
}

char	*ft_takeword(char *buffer)
{
	char	*word;
	int		a;

	a = 0;
	if (!buffer[a])
		return (NULL);
	while (buffer[a] && buffer[a] != '\n')
		a++;
	word = ft_calloc(a + 2, sizeof(char));
	a = 0;
	while (buffer[a] && buffer[a] != '\n')
	{
		word[a] = buffer[a];
		a++;
	}
	if (buffer[a] && buffer[a] == '\n')
		word[a++] = '\n';
	return (word);
}

char	*ft_remains(char *buffer)
{
	char	*remains;
	int		a;
	int		b;

	a = 0;
	while (buffer[a] && buffer[a] != '\n')
		a++;
	if (!buffer[a])
	{
		free(buffer);
		return (NULL);
	}
	remains = ft_calloc((ft_strlen(buffer) - a + 1), sizeof(char));
	a++;
	b = 0;
	while (buffer[a])
		remains[b++] = buffer[a++];
	if (buffer)
		free(buffer);
	return (remains);
}

char	*read_line(char *str, int fd)
{
	char	*buffer;
	int		read_byte;

	if (!str)
		str = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = 0;
		str = ft_joinfree(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (buffer)
		free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*word;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(buffer, fd);
	if (!buffer)
		return (NULL);
	word = ft_takeword(buffer);
	buffer = ft_remains(buffer);
	return (word);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s <file_path>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Line : %s", line);
		break ;
		free(line);
	}
	close(fd);
	return (0);
}
*/