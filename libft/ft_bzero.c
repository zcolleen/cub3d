/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 03:45:21 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/01 03:33:43 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			in;
	unsigned char	*p;

	p = (unsigned char *)s;
	in = 0;
	while (in < n)
	{
		p[in] = '\0';
		in++;
	}
}
