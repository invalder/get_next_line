/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:06:13 by nnakarac          #+#    #+#             */
/*   Updated: 2022/03/02 19:03:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <bsd/string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*get_next_line(int fd);
char	*gnl_read_to_left_str(int fd, char *left_str);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *left_str, char *buff);
size_t	gnl_strlen(char *s);
char	*gnl_get_line(char *left_str);
char	*gnl_store_newline(char *left_str);

#endif
