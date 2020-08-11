/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:43:31 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 15:53:25 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	split_bytes(int size, unsigned char *header)
{
	header[0] = ((unsigned char)size);
	header[1] = ((unsigned char)(size >> 8));
	header[2] = ((unsigned char)(size >> 16));
	header[3] = ((unsigned char)(size >> 24));
}

int		col_limit(int col_hight, t_img *myimg)
{
	if (col_hight == 0)
		col_hight = 1;
	if (col_hight >= myimg->plane_y)
		col_hight = myimg->plane_y;
	return (col_hight);
}

void	put_x_in_image(t_img *myimg)
{
	if (myimg->text->flag == 1)
		myimg->text->square_coord = myimg->text->square_coord_hor
		- (int)(myimg->text->square_coord_hor / RES) * RES;
	else if (myimg->text->flag == 4)
		myimg->text->square_coord = (int)(myimg->text->square_coord_hor / RES)
		* RES + RES - myimg->text->square_coord_hor;
	else if (myimg->text->flag == 3)
		myimg->text->square_coord = myimg->text->square_coord_vert
		- (int)(myimg->text->square_coord_vert / RES) * RES;
	else if (myimg->text->flag == 2)
		myimg->text->square_coord = (int)(myimg->text->square_coord_vert / RES)
		* RES + RES - myimg->text->square_coord_vert;
}

void	player_coordinates(int i, int j, t_img *data, int orient)
{
	data->play->i = i;
	data->play->j = j;
	data->play->x = j * RES + RES / 2 - 1;
	data->play->y = i * RES + RES / 2 - 1;
	data->play->orientation = orient;
}

int		ft_isplayer(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (2);
	if (c == 'E')
		return (3);
	if (c == 'W')
		return (4);
	return (0);
}
