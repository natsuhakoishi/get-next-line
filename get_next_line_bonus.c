/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa <yyean-wa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:39:29 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/11/15 17:22:59 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buffer[OPEN_MAX];
	char		*word;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = read_line(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	word = ft_takeword(buffer[fd]);
	buffer[fd] = ft_remains(buffer[fd]);
	return (word);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	if (argc != 3)
	{
		printf("Usage: %s <file_path_1> <file_path_2>\n", argv[0]);
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 && fd2 < 0)
	{
		perror("Error opening file");
		return (1);
	}
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	while (line1 != NULL && line2 != NULL)
	{
		printf("Line for file 1: %s", line1);
		printf("Line for file 2: %s", line2);
		break ;
		free(line1);
		free(line2);
	}
	close(fd1);
	close(fd2);
	return (0);
}
*/