/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:33:50 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 18:05:42 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		scip_digit(char *line)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int		check_line_f_c(char *line)
{
	if (*line == ',' && ft_isdigit(*(line + 1)))
		return (0);
	else
	{
		ft_putstr_fd("Error:\nbad color line\n", 1);
		return (-1);
	}
}

int		check_color(int i)
{
	if (i < 0 || i > 255)
		return (-1);
	return (0);
}

int		filler(char *line, int *i, int *j, int *k)
{
	if ((check_color(*i = ft_atoi(line))) == -1)
		return (-1);
	line = line + scip_digit(line);
	if (check_line_f_c(line) == 0)
		line++;
	else
		return (-1);
	if ((check_color(*j = ft_atoi(line))) == -1)
		return (-1);
	line = line + scip_digit(line);
	if (check_line_f_c(line) == 0)
		line++;
	else
		return (-1);
	if ((check_color(*k = ft_atoi(line))) == -1)
		return (-1);
	return (0);
}

int		allocator_f_c(char *line, t_img *myimg, char c)
{
	if (c == 'F')
	{
		myimg->reader->flag_floor = 1;
		return (filler(line, &(myimg->reader->r_f), &(myimg->reader->g_f),
		&(myimg->reader->b_f)));
	}
	if (c == 'C')
	{
		myimg->reader->flag_cell = 1;
		return (filler(line, &(myimg->reader->r_c), &(myimg->reader->g_c),
		&(myimg->reader->b_c)));
	}
	return (0);
}
