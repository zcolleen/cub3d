/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:11:25 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/03 19:38:17 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find(char const *s, unsigned int start)
{
	unsigned int i;

	i = 0;
	while (i != start)
		i++;
	if (i > ft_strlen(s))
		return (NULL);
	return ((char *)(s + i));
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;
	char *ptr;

	if (s == NULL)
		return (NULL);
	sub = find(s, start);
	if (sub == NULL)
		return (ft_calloc(1, sizeof(char)));
	ptr = (char *)malloc(sizeof(*ptr) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, sub, (len + 1));
	return (ptr);
}
