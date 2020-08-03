/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 00:04:35 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/01 01:21:44 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	null(char *dst, const char *src, size_t size, size_t i)
{
	size_t j;

	j = 0;
	while (i < size - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t t;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < size)
		i++;
	if (dst[i] != '\0')
	{
		t = size;
		return (t + ft_strlen(src));
	}
	else
	{
		t = ft_strlen(dst);
		null(dst, src, size, i);
	}
	return (t + ft_strlen(src));
}
