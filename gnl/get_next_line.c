/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 19:50:50 by zcolleen          #+#    #+#             */
/*   Updated: 2020/06/11 13:18:42 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		fr(char *p, char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	free(p);
	return (-1);
}

int		line_copy(char **line, char *s)
{
	int i;

	i = 0;
	free(*line);
	while (s[i] != '\0')
		i++;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (fr(NULL, &s));
	(*line)[i] = '\0';
	copy(s, line);
	return (0);
}

int		concatination(char **line, char **s)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (*s)
	{
		if ((p = search_for_n(*s)))
		{
			while ((*s)[j] != '\0')
				j++;
			*p = '\0';
			if ((line_copy(line, *s)) == -1)
				return (-1);
			while (++p < *s + j)
				(*s)[i++] = *p;
			(*s)[i] = '\0';
			return (1);
		}
		if (line_copy(line, *s) == -1)
			return (-1);
		fr(NULL, s);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char			buf[BUFFER_SIZE + 1];
	ssize_t				bytes;
	static char			*s;
	char				*t;
	int					i;

	if (fd < 0 || line == NULL || (!(*line = (char *)malloc(sizeof(char)))))
		return (fr(NULL, &s));
	(*line)[0] = '\0';
	bytes = 1;
	if ((i = concatination(line, &s)) == -1)
		return (-1);
	while ((i == 0) && (bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if ((t = search_for_n(buf)))
			return (!(s = s_save(++t, s)) ? fr(*line, &s) : loc(buf, line, &s));
		buf[bytes] = '\n';
		if (loc(buf, line, &s) == -1)
			return (-1);
	}
	if (bytes == -1)
		return (fr(*line, &s));
	return ((bytes == 0 && !(s)) ? 0 : 1);
}
