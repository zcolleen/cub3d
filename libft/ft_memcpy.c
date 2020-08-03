/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 03:58:31 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/01 03:37:20 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned const char	*p1;
	unsigned char		*p2;
	size_t				i;

	i = 0;
	p1 = (unsigned const char *)source;
	p2 = (unsigned char *)destination;
	while (i < n)
	{
		p2[i] = p1[i];
		i++;
	}
	return (destination);
}
