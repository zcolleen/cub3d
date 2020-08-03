/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 21:24:40 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/07 08:49:35 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*g;
	size_t			in;

	in = 0;
	p = (unsigned char *)s1;
	g = (unsigned char *)s2;
	while (in < n)
	{
		if (p[in] != g[in])
			return (p[in] - g[in]);
		in++;
	}
	return (0);
}
