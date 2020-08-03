/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:56:14 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/11 17:36:48 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	scip(const char *nptr)
{
	int i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\v' ||
			nptr[i] == '\f')
		i++;
	return (i);
}

static int	sign(const char *nptr, int i)
{
	if (nptr[i] == '-')
		return (-1);
	else
		return (1);
}

int			ft_atoi(const char *nptr)
{
	int		i;
	long	d;
	int		c;

	d = 0;
	i = scip(nptr);
	c = sign(nptr, i);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] != '\0')
	{
		if ((d * 10 < d) && c == 1)
			return (-1);
		if ((d * 10 < d) && c == -1)
			return (0);
		if (!ft_isdigit(nptr[i]))
			return ((int)(c * d));
		d = d * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)(c * d));
}
