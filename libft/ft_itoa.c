/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:41:43 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/07 08:50:51 by zcolleen         ###   ########.fr       */
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
	if (n < 0)
		s++;
	return (s);
}

static void	record(char *ptr, int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		while (n / 10 != 0)
		{
			ptr[i] = -(n % 10 - '0');
			n = n / 10;
			i++;
		}
		ptr[i] = -(n % 10 - '0');
	}
	else
	{
		while (n / 10 != 0)
		{
			ptr[i] = n % 10 + '0';
			n = n / 10;
			i++;
		}
		ptr[i] = n % 10 + '0';
	}
	i++;
	ptr[i] = '\0';
}

static void	reverse(char *ptr)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(ptr) - 1;
	while (i < j)
	{
		c = ptr[i];
		ptr[i] = ptr[j];
		ptr[j] = c;
		i++;
		j--;
	}
}

char		*ft_itoa(int n)
{
	char *ptr;

	ptr = (char *)malloc(sizeof(*ptr) * (number(n) + 1));
	if (ptr == NULL)
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		record(ptr + 1, n);
		reverse(ptr + 1);
	}
	else
	{
		record(ptr, n);
		reverse(ptr);
	}
	return (ptr);
}
