/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 13:01:20 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:12:14 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int			take_color_from_sprite(t_img *myimg, int x,
int top_point, int col_hight)
{
	int	*data;
	int y;

	x = (int)((x - myimg->sprite->image_x) * (RES / col_hight));
	y = (int)((top_point - myimg->sprite->image_y) * (RES / col_hight));
	data = (int*)(myimg->sprite->addr + y * myimg->sprite->line_length +
	x * (myimg->sprite->bits_per_pixel / 8));
	return (*data);
}

void		draw_sprite_col(t_img *myimg, int x, int col_hight)
{
	int		top_point;
	int		color;
	double	save_col;
	double	save_top;

	save_col = col_hight;
	save_top = (int)fabs((myimg->plane_y / 2.0) - (col_hight / 2.0));
	if (col_hight > myimg->plane_y)
		col_hight = myimg->plane_y;
	top_point = (int)((myimg->plane_y / 2.0) - (col_hight / 2.0));
	myimg->sprite->image_y = top_point;
	col_hight = col_hight + top_point;
	while (top_point < col_hight)
	{
		if ((color = take_color_from_sprite(myimg, x, save_top, save_col)) > 0)
			put_pixel(myimg, x, top_point, color);
		top_point++;
		save_top++;
	}
}

void		draw_sprite(t_img *myimg, double trace,
int col_hight, t_one_spr *point)
{
	int		x;
	double	right_point;

	x = (int)((myimg->plane_x / (PI / 3.0)) * trace);
	myimg->sprite->image_x = x;
	right_point = x + col_hight;
	if (right_point > myimg->plane_x)
		right_point = myimg->plane_x;
	if (x < 0)
		x = 0;
	while (x < right_point)
	{
		if (myimg->sprite->dis_mass[x] > point->dist_to_sprite)
			draw_sprite_col(myimg, x, col_hight);
		x++;
	}
}

void		sprite_trace(t_one_spr *point, t_img *myimg)
{
	if ((myimg->sprite->trace = atan((point->y - myimg->play->y) /
	(point->x - myimg->play->x))) < 0)
	{
		if ((point->y - myimg->play->y) < 0)
			myimg->sprite->trace = myimg->sprite->trace + 2.0 * PI;
		else
			myimg->sprite->trace = myimg->sprite->trace + PI;
	}
	else
	{
		if ((point->x - myimg->play->x) < 0)
			myimg->sprite->trace = myimg->sprite->trace + PI;
	}
}

void		sprite_drawer(t_img *myimg)
{
	double		trace;
	int			col_hight;
	double		proj_dist;
	t_one_spr	*point;

	proj_dist = (myimg->plane_x / 2.0) / tan(PI / 6.0);
	point = myimg->sprite->head;
	while (point != NULL)
	{
		point->dist_to_sprite = sqrt(pow((myimg->play->x - point->x), 2.0) +
		pow((myimg->play->y - point->y), 2.0));
		point = point->next;
	}
	list_sort(&(myimg->sprite->head));
	point = myimg->sprite->head;
	while (point != NULL)
	{
		col_hight = (int)((((myimg->plane_y * proj_dist)) / 2.0)
		/ (SCALE * point->dist_to_sprite));
		sprite_trace(point, myimg);
		trace = fix_angle(myimg, col_hight);
		if (trace != -1)
			draw_sprite(myimg, trace, col_hight, point);
		point = point->next;
	}
}
