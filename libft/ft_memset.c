/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 02:25:25 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/01 03:34:44 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t			in;
	unsigned char	*p;

	p = (unsigned char *)destination;
	in = 0;
	while (in < n)
	{
		p[in] = c;
		in++;
	}
	return (destination);
}
