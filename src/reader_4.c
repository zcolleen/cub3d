/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:31:22 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 18:05:37 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		parcer_f_c(char *line, t_img *myimg, char c)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (allocator_f_c(line + i, myimg, c));
	else
	{
		ft_putstr_fd("Error:\nwrong color line\n", 1);
		return (-1);
	}
}

int		check_line_res(char *line)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (i);
	else
	{
		ft_putstr_fd("Error:\nbad resolution line\n", 1);
		return (-1);
	}
}

int		allocator_r(char *line, t_img *myimg)
{
	int i;

	myimg->reader->r_x = ft_atoi(line);
	if ((i = check_line_res(line)) == -1)
		return (-1);
	line = line + i;
	myimg->reader->r_y = ft_atoi(line);
	return (0);
}

int		parcer_r(char *line, t_img *myimg)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		myimg->reader->flag_res = 1;
		return (allocator_r(line + i, myimg));
	}
	else
	{
		ft_putstr_fd("Error:\nbad resolution line\n", 1);
		return (-1);
	}
}

int		parce_line(t_img *myimg, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0' && line[i + 1] != '\0')
		i++;
	if (line[i] == 'S' && line[i + 1] != 'O' && !(myimg->reader->flag_sp))
		return (parcer(line + i + 1, myimg, line[i], 0));
	else if ((line[i] == 'N' && line[i + 1] == 'O' &&
	!(myimg->reader->flag_n)) ||
	(line[i] == 'S' && line[i + 1] == 'O' && !(myimg->reader->flag_s)) ||
	(line[i] == 'W' && line[i + 1] == 'E' && !(myimg->reader->flag_w))
	|| (line[i] == 'E' && line[i + 1] == 'A' && !(myimg->reader->flag_e)))
		return (parcer(line + i + 2, myimg, line[i], 1));
	else if (line[i] == 'F' && !(myimg->reader->flag_floor))
		return (parcer_f_c(line + i + 1, myimg, line[i]));
	else if (line[i] == 'C' && !(myimg->reader->flag_cell))
		return (parcer_f_c(line + i + 1, myimg, line[i]));
	else if (line[i] == 'R' && !(myimg->reader->flag_res))
		return (parcer_r(line + i + 1, myimg));
	else if (line[i] != ' ' && line[i] != '\0')
	{
		ft_putstr_fd("Error:\nbad line in file\n", 1);
		return (-1);
	}
	return (0);
}
