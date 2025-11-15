/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsisli <dsisli@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 06:38:16 by dsisli            #+#    #+#             */
/*   Updated: 2025/11/15 10:16:44 by dsisli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*g_track = NULL;

char	*ft_gnl_make_line(int fd, char *track)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytesread;

	while (!gnl_strchr(track, '\n'))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
		{
			if (track)
			{
				free(track);
				track = NULL;
			}
			return (NULL);
		}
		if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		track = gnl_strjoin(track, buffer);
		if (!track)
			return (NULL);
	}
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
	rest_len = gnl_strlen(*track) - len;
	rest = gnl_substr(*track, len, rest_len);
	free(*track);
	*track = rest;
	return (line);
}

void	free_gnl_track(void)
{
	if (g_track)
	{
		free(g_track);
		g_track = NULL;
	}
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	g_track = ft_gnl_make_line(fd, g_track);
	if (!g_track || *g_track == '\0')
	{
		if (g_track)
		{
			free(g_track);
			g_track = NULL;
		}
		return (NULL);
	}
	line = extract_line(&g_track);
	return (line);
}
