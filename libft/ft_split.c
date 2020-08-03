/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 17:14:13 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/06 19:31:50 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **ptr)
{
	int i;

	i = 0;
	while (*(ptr + i) != NULL)
	{
		free(*(ptr + i));
		i++;
	}
	free(ptr);
}

static int	counter(char const *s, char c)
{
	int flag;
	int count;
	int i;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static int	count_word(const char *s, int i, char c)
{
	int count;

	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static int	record(char *ptr, char const *s, char c, int i)
{
	int j;

	j = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		ptr[j] = s[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (i);
}

char		**ft_split(char const *s, char c)
{
	char**ptr;
	int i;
	int ch;
	int j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	ch = counter(s, c);
	if ((ptr = (char **)malloc(sizeof(*ptr) * (ch + 1))) == NULL)
		return (NULL);
	while (ch-- != 0)
	{
		*(ptr + i) = (char *)malloc(sizeof(**ptr) * (count_word(s, j, c) + 1));
		if (*(ptr + i) == NULL)
		{
			ft_free(ptr);
			return (NULL);
		}
		j = record(*(ptr + i), s, c, j);
		i++;
	}
	*(ptr + i) = NULL;
	return (ptr);
}
