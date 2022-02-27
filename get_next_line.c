/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:13:44 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/28 00:58:05 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
char	*gnl_strndup(char *dest, char *src, size_t n);
char	*gnl_store_line(char *store_line, char *read_line, int read_cnt);
size_t	gnl_strlen(char *str);

char	*get_next_line(int fd)
{
	static char	*store_line = NULL;
	char		*read_line;
	char		*tmp_line;
	int			read_cnt;
	int			ent;

	ent = 0;
	tmp_line = NULL;
	read_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_line || read(fd, NULL, 0) < 0)
		return (NULL);
	read_cnt = read(fd, read_line, BUFFER_SIZE);
	printf("read_line: %s\n", read_line);
	store_line = gnl_store_line(store_line, read_line, read_cnt);
	printf("store_line: %s\n", store_line);
	while (*(store_line + ent) != '\n' && *(store_line + ent))
		ent++;
	if (*(store_line + ent) != '\n')
		ent = 0;
	if (ent && *(store_line + ent) == '\n')
	{
		free(read_line);
		read_line = gnl_strndup(read_line, store_line, ent + 1);
		tmp_line = gnl_strndup(tmp_line, store_line + ent + 1, strlen(store_line + ent + 1));
		if (!read_line || !tmp_line)
			return (NULL);
		*(read_line + ent + 1) = '\0';
		*(tmp_line + strlen(store_line + ent + 1)) = '\0';
		free(store_line);
		store_line = NULL;
		store_line = gnl_strndup(store_line, tmp_line, strlen(tmp_line));
		*(store_line + strlen(tmp_line)) = '\0';
		return (read_line);
	}
	return (NULL);
}

char	*gnl_store_line(char *store_line, char *read_line, int read_cnt)
{
	char	*tmp_line;

	tmp_line = NULL;
	if (!store_line)
	{
		store_line = gnl_strndup(store_line, read_line, read_cnt);
		if (!store_line)
			return (NULL);
		*(store_line + read_cnt) = 0;
	}
	else
	{
		tmp_line = gnl_strndup(tmp_line, store_line, gnl_strlen(store_line));
		if (!tmp_line)
			return (NULL);
		*(tmp_line + gnl_strlen(store_line)) = '\0';
		free(store_line);
		store_line = malloc(sizeof(char) * (read_cnt + gnl_strlen(tmp_line) + 1));
		store_line = gnl_strndup(store_line, tmp_line, gnl_strlen(tmp_line));
		gnl_strndup(store_line + gnl_strlen(tmp_line), read_line, read_cnt);
		*(store_line + read_cnt + gnl_strlen(tmp_line)) = 0;
	}
	return (store_line);
}

size_t	gnl_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*gnl_strndup(char *dest, char *src, size_t n)
{
	size_t	cnt;

	cnt = 0;
	if (n == 0)
		n = gnl_strlen(src);
	if(!dest)
	{
		dest = malloc(sizeof(char) * (n + 1));
		if (!dest)
			return (NULL);
	}
	while (cnt < n)
	{
		*(dest + cnt) = *(src + cnt);
		cnt++;
	}
	return (dest);
}

void	gnl(int fd, char const *expectedReturn)
{
	char	*gnl_return;

	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	gnl_return = get_next_line(fd);
	if (expectedReturn == NULL)
	{
		if (gnl_return == NULL)
			printf("Exp: NULL\nRes: NULL\n");
		else
			printf("Exp: NULL\nRes: %s\n", gnl_return);
	}
	else
	{
		if (!strcmp(gnl_return, expectedReturn))
			printf("Exp: %s\nRes: %s\n", expectedReturn, gnl_return);
		else
			printf("Exp: %s\nRes: %s\n", expectedReturn, gnl_return);
	}
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	free(gnl_return);
}

int	main(void)
{
	int	fd;

	fd = open("gnlTester/files/multiple_line_with_nl", O_RDWR);
	/* 1 */ gnl(fd, "9876543210987654321098765432109876543210\n");
	/* 2 */ gnl(fd, "01234567890123456789012345678901234567890\n");
	/* 3 */ gnl(fd, "987654321098765432109876543210987654321098\n");
	/* 4 */ gnl(fd, "01234567890123456789012345678901234567890\n");
	/* 5 */ gnl(fd, "9876543210987654321098765432109876543210\n");
	/* 6 */ gnl(fd, NULL);
	close(fd);

}
