/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 03:44:39 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/02 20:55:08 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t l;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	l = ft_strlen(little);
	if (ft_strlen(big) == 0)
		return (NULL);
	while (i < len)
	{
		if (ft_strncmp(big + i, little, l) == 0 && (i + l - 1) < len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
