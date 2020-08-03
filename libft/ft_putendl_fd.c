/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:04:58 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/07 08:51:42 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	c;
	int		l;

	if (s == NULL)
		return ;
	c = '\n';
	l = ft_strlen(s);
	write(fd, s, l);
	write(fd, &c, 1);
}
