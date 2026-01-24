/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsisli <dsisli@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:57:53 by dsisli            #+#    #+#             */
/*   Updated: 2025/11/15 10:17:20 by dsisli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (!s)
		return (NULL);
	ch = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	s = src;
	d = dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*gnl_strjoin(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	if (s1 != NULL)
		len1 = gnl_strlen(s1);
	else
		len1 = 0;
	if (s2 != NULL)
		len2 = gnl_strlen(s2);
	else
		len2 = 0;
	out = malloc(len1 + len2 + 1);
	if (!out)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
		ft_memcpy(out, s1, len1);
	if (s2)
		ft_memcpy(out + len1, s2, len2);
	out[len1 + len2] = '\0';
	free(s1);
	return (out);
}

char	*gnl_substr(char *s, int start, size_t len)
{
	char	*ss;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start < 0)
		start = 0;
	if ((size_t)start > s_len)
	{
		ss = malloc(1);
		if (!ss)
			return (NULL);
		ss[0] = '\0';
		return (ss);
	}
	if (len > gnl_strlen(s + start))
		len = gnl_strlen(s + start);
	ss = malloc(len + 1);
	if (!ss)
		return (NULL);
	ft_memcpy(ss, s + start, len);
	ss[len] = '\0';
	return (ss);
}
