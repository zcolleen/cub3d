/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:10:33 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/09 18:50:25 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number(int n)
{
	int s;

	s = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		s++;
	}
	return (s);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		num;
	int		tem;
	int		i;
	char	c;

	i = number(n);
	if (n < 0)
		write(fd, "-", 1);
	while (i > 0)
	{
		tem = n;
		num = i;
		while (--num > 0)
			tem = tem / 10;
		c = (n > 0) ? (tem % 10 + '0') : -(tem % 10 - '0');
		write(fd, &c, 1);
		i--;
	}
}
