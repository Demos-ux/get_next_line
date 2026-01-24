/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsisli <dsisli@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 06:38:16 by dsisli            #+#    #+#             */
/*   Updated: 2026/01/22 19:18:51 by dsisli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_make_line(int fd, char *track)
{
	char	*buf;
	ssize_t	len;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	len = 1;
	while (!gnl_strchr(track, '\n') && len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
		{
			free(buf);
			free(track);
			return (NULL);
		}
		if (len > 0)
		{
			buf[len] = '\0';
			track = gnl_strjoin(track, buf);
		}
	}
	free(buf);
	return (track);
}

char	*extract_line(char **track)
{
	size_t	len;
	size_t	rest_len;
	char	*line;
	char	*rest;

	if (!track || !*track || **track == '\0')
		return (NULL);
	if (gnl_strchr(*track, '\n'))
		len = gnl_strchr(*track, '\n') - *track + 1;
	else
		len = gnl_strlen(*track);
	line = gnl_substr(*track, 0, len);
	if (!line)
		return (NULL);
	rest_len = gnl_strlen(*track) - len;
	rest = gnl_substr(*track, len, rest_len);
	if (!rest)
	{
		free(line);
		return (NULL);
	}
	free(*track);
	*track = rest;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*track;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	track = ft_gnl_make_line(fd, track);
	if (!track || *track == '\0')
	{
		free(track);
		track = NULL;
		return (NULL);
	}
	line = extract_line(&track);
	return (line);
}
