/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:25:13 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 18:05:32 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		check_for_elem(t_img *myimg)
{
	if (myimg->reader->flag_cell && myimg->reader->flag_floor &&
	myimg->reader->flag_e && myimg->reader->flag_n && myimg->reader->flag_s &&
	myimg->reader->flag_w && myimg->reader->flag_sp &&
	myimg->reader->flag_res)
		return (1);
	return (0);
}

void	check_follower(int follower, t_img *myimg, char *line)
{
	if (follower == -1)
	{
		cleaner(myimg);
		exit(1);
	}
	if (follower == 0 && check_for_elem(myimg) != 1)
	{
		free(line);
		cleaner(myimg);
		ft_putstr_fd("Error\nmissing element\n", 1);
		exit(0);
	}
}

void	get_l(int fd, t_img *myimg, int *j)
{
	int		follower;
	char	*line;

	while ((follower = get_next_line(fd, &line)) > 0)
	{
		if (parce_line(myimg, line) == -1)
		{
			cleaner(myimg);
			ft_putstr_fd("Error:\nwrong configuration", 1);
			exit(0);
		}
		myimg->skip++;
		free(line);
		if ((check_for_elem(myimg)) == 1)
			break ;
	}
	check_follower(follower, myimg, line);
	while ((follower = get_next_line(fd, &line)) > 0)
	{
		(*j)++;
		free(line);
	}
	if (ft_strlen(line))
		(*j)++;
	free(line);
}

int		check_for_valid_char(char c)
{
	if (c == ' ' || c == '\0' || c == '1' ||
	c == '2' || c == '0')
		return (1);
	if (c == 'S' || c == 'W' ||
	c == 'E' || c == 'N')
		return (0);
	return (-1);
}

void	clean_exit(t_img *myimg)
{
	cleaner(myimg);
	ft_putstr_fd("Error:\ninvalid char", 1);
	exit(0);
}
