/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 16:35:10 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/10 19:55:45 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + y * data->line_length + x * (data->bits_per_pixel / 8);
	*(unsigned int*)dst = color;
}

int		take_color(t_img *myimg, int y, double k)
{
	unsigned int	*data;
	int				x;

	data = NULL;
	y = (int)(k * y);
	x = myimg->text->square_coord;
	if (myimg->text->flag == 1)
		data = (unsigned int*)(myimg->north->addr + y *
		myimg->north->line_length + x * (myimg->north->bits_per_pixel / 8));
	else if (myimg->text->flag == 4)
		data = (unsigned int*)(myimg->south->addr + y
		* myimg->south->line_length + x * (myimg->south->bits_per_pixel / 8));
	else if (myimg->text->flag == 3)
		data = (unsigned int*)(myimg->west->addr + y
		* myimg->west->line_length + x * (myimg->west->bits_per_pixel / 8));
	else if (myimg->text->flag == 2)
		data = (unsigned int*)(myimg->east->addr + y
		* myimg->east->line_length + x * (myimg->east->bits_per_pixel / 8));
	return (*data);
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

void	drowing_cell(int x, int y_point, t_img *myimg)
{
	int i;

	i = 0;
	while (i < y_point)
	{
		put_pixel(myimg, x, i, myimg->f_c->cell_col);
		i++;
	}
}

void	drowing_floor(int col_hight, int x, t_img *myimg)
{
	int i;

	i = col_hight;
	while (i < myimg->plane_y)
	{
		put_pixel(myimg, x, i, myimg->f_c->floor_col);
		i++;
	}
}

int		col_limit(int col_hight, t_img *myimg)
{
	if (col_hight == 0)
		col_hight = 1;
	if (col_hight >= myimg->plane_y)
		col_hight = myimg->plane_y;
	return (col_hight);
}

void	proector(double distance, t_img *myimg, int x)
{
	int		col_hight;
	int		top_point;
	int		y_point;
	double	save_col;
	double	save_top;

	col_hight = (int)((((myimg->plane_y * (myimg->plane_x / 2.0) /
	tan(PI / 6.0))) / 2.0) / (SCALE * distance));
	save_col = col_hight;
	save_top = (int)fabs((myimg->plane_y / 2.0) - (col_hight / 2.0));
	col_hight = col_limit(col_hight, myimg);
	top_point = (myimg->plane_y / 2.0) - (col_hight / 2.0);
	y_point = top_point;
	put_x_in_image(myimg);
	col_hight = col_hight + top_point;
	drowing_cell(x, y_point, myimg);
	while (top_point < col_hight)
	{
		put_pixel(myimg, x, top_point,
		take_color(myimg, save_top - y_point, RES / save_col));
		top_point++;
		save_top++;
	}
	drowing_floor(col_hight, x, myimg);
}
