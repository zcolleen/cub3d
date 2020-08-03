/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:39:15 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/03 16:50:46 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	le;

	le = ft_strlen(s) + 1;
	ptr = (char *)malloc(sizeof(*ptr) * le);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, le);
	return (ptr);
}
