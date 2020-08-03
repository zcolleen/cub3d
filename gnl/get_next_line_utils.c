/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:50:28 by zcolleen          #+#    #+#             */
/*   Updated: 2020/06/11 13:09:33 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		copy(char *tmp, char **line)
{
	int i;

	i = 0;
	while (tmp[i] != '\0')
	{
		(*line)[i] = tmp[i];
		i++;
	}
	return (i);
}

int		loc(char *buffer, char **line, char **s)
{
	int	i;
	char*tmp;
	int	j;
	int	size;

	j = 0;
	i = 0;
	size = 0;
	while (buffer[size] != '\n')
		size++;
	tmp = *line;
	while ((*line)[i] != '\0')
		i++;
	if (!(*line = (char *)malloc(sizeof(char) * (size + i + 1))))
		return (fr(tmp, s));
	i = copy(tmp, line);
	while (buffer[j] != '\n')
	{
		(*line)[i] = buffer[j];
		i++;
		j++;
	}
	(*line)[i] = '\0';
	free(tmp);
	return (1);
}

char	*search_for_n(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (buffer + i);
		i++;
	}
	return (NULL);
}

char	*s_save(char *pointer, char *s)
{
	int	i;

	i = 0;
	while (pointer[i] != '\0')
		i++;
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i] = '\0';
	i = 0;
	while (pointer[i] != '\0')
	{
		s[i] = pointer[i];
		i++;
	}
	return (s);
}
