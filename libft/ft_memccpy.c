/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 04:17:52 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/10 05:54:25 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	const unsigned char	*p1;
	unsigned char		*p2;
	size_t				i;
	unsigned char		ch;

	i = 0;
	p1 = (const unsigned char *)source;
	p2 = (unsigned char *)destination;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (p1[i] == ch)
		{
			p2[i] = ch;
			return (destination + i + 1);
		}
		p2[i] = p1[i];
		i++;
	}
	return (NULL);
}
