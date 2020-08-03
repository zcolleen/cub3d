/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:26:15 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/06 17:13:22 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	remove(char *ptr)
{
	int i;

	i = 0;
	while (ptr[i] != '\0')
	{
		ptr[i] = ptr[i + 1];
		i++;
	}
}

static void	checker_up(char const *set, char *ptr)
{
	int j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == ptr[0])
		{
			remove(ptr);
			checker_up(set, ptr);
		}
		j++;
	}
}

static void	checker_down(char const *set, char *ptr, int i)
{
	int j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == ptr[i])
		{
			remove(ptr + i);
			i--;
			checker_down(set, ptr, i);
		}
		j++;
	}
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char*ptr;
	int i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	ptr = ft_strdup(s1);
	if (ptr == NULL)
		return (NULL);
	if (set[0] == '\0')
		return (ptr);
	checker_up(set, ptr);
	i = ft_strlen(ptr) - 1;
	checker_down(set, ptr, i);
	return (ptr);
}
