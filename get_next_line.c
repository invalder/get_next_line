/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:05:57 by nnakarac          #+#    #+#             */
/*   Updated: 2022/03/02 19:02:59 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_store_line(int fd, char *stored)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!gnl_strchr(stored, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		stored = gnl_strjoin(stored, buff);
	}
	free(buff);
	return (stored);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stored = gnl_store_line(fd, stored);
	if (!stored)
		return (NULL);
	line = gnl_get_line(stored);
	stored = gnl_store_newline(stored);
	return (line);
}

char	*gnl_store_newline(char *stored)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (gnl_strlen(stored) - i));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stored[i])
		str[j++] = stored[i++];
	str[j] = '\0';
	free(stored);
	return (str);
}
