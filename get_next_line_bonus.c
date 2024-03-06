/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:10:31 by haalouan          #+#    #+#             */
/*   Updated: 2023/12/10 11:47:22 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*first_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
	{
		buffer = NULL;
		return (free(buffer), NULL);
	}
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(ft_strlen(buffer) - i + 1);
	if (!line)
	{
		buffer = NULL;
		return (free(buffer), NULL);
	}
	j = 0;
	while (buffer[i] != '\0')
		line[j++] = buffer[i++];
	line[j++] = '\0';
	return (free(buffer), line);
}

char	*ft_read(int fd, char *buffer)
{
	char	*temp;
	int		byte_read;

	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	temp = malloc((size_t)BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	byte_read = 1;
	while (!ft_strchr(buffer, '\n') && byte_read > 0)
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), free(temp), NULL);
		if (byte_read == 0)
			break ;
		temp[byte_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	return (free(temp), buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE > INT_MAX || BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (ft_strlen(buffer[fd]) == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = first_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), NULL);
	buffer[fd] = next_line(buffer[fd]);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		free(line);
		return (NULL);
	}
	return (line);
}
