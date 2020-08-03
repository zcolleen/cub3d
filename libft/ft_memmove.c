/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:11:32 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/01 03:36:52 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sor_more(unsigned char *tem, unsigned char *des,
		unsigned const char *sor, size_t n)
{
	while (n--)
	{
		*tem = sor[n];
		des[n] = *tem;
	}
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		tem;
	unsigned char		*des;
	unsigned const char	*sor;
	size_t				i;

	i = 0;
	des = (unsigned char *)dest;
	sor = (unsigned const char *)src;
	if (des > sor)
		sor_more(&tem, des, sor, n);
	else
	{
		while (i < n)
		{
			tem = sor[i];
			des[i] = tem;
			i++;
		}
	}
	return (dest);
}
