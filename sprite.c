/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 13:01:20 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/04 20:25:32 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	fix_angles(t_img *myimg)
{
	double trace;

	trace = myimg->play->trace;
	while (myimg->sprite->trace > 2 * PI)
		myimg->sprite->trace = myimg->sprite->trace - 2 * PI;
	while (myimg->sprite->trace <= 0)
		myimg->sprite->trace = myimg->sprite->trace + 2 * PI;
	while (trace > 2 * PI)
		trace = trace - 2 * PI;
	while (trace <= 0)
		trace = trace + 2 * PI;
	return (trace);
}

double	check_vision(t_img *myimg, double trace)
{
	double fixed;

	fixed = 0;
	if (trace + PI / 3.0 > 2.0 * PI)
	{
		fixed = trace + PI / 3.0 - 2.0 * PI;
		if (fixed > myimg->sprite->trace)
			return (2.0 * PI - (trace - myimg->sprite->trace));
		else if (myimg->sprite->trace > trace)
			return (myimg->sprite->trace - trace);
		else
			return (-1);
	}
	if ((trace < myimg->sprite->trace) && ((trace + PI / 3.0) > myimg->sprite->trace))//trace - угол перса
		return (myimg->sprite->trace - trace);
	return (-1);
}

int		init_sprite(t_img *myimg)
{
	t_sprite *sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (-1);
	if (!(sprite->dis_mass = (double *)malloc(sizeof(double) * myimg->plane_x)))
		return (-1);
	myimg->sprite = sprite;
	myimg->sprite->path_to_sprite = myimg->reader->path_to_sprite;
	myimg->sprite->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->sprite->path_to_sprite, &(myimg->sprite->width), &(myimg->sprite->hight));
	myimg->sprite->addr = mlx_get_data_addr(myimg->sprite->img, &(myimg->sprite->bits_per_pixel), &(myimg->sprite->line_length), &(myimg->sprite->endian));
	return (0);
}

void	draw_sprite_col(t_img *myimg, double save, int x, int col_hight)
{
	double top_point;

//	proj_dist = (myimg->plane_x / 2.0) / tan(PI / 6.0);
	top_point = (myimg->plane_y / 2.0) - (col_hight / 2.0);
	col_hight = col_hight + top_point;
	while (top_point < col_hight)
	{
		put_pixel(myimg, x, top_point, 0x000000);
		top_point++;
	}
}

void	draw_sprite(t_img *myimg, double save)
{
	int		col_hight;
	int		x;
	double	right_point;

	col_hight = (int)((((myimg->plane_y * (myimg->plane_x / 2.0) / tan(PI / 6.0))) / 2.0) / (SCALE * myimg->sprite->dist_to_sprite));
	x = save / (PI / 3.0);
	right_point = x + col_hight;
	while (x < right_point)
	{
		draw_sprite_col(myimg, save, x, col_hight);
		x++;
	}
}

void	sprite_drawer(t_img *myimg)
{
	double trace;
	double save;

	init_sprite(myimg);
	myimg->sprite->x = 24.0 * RES + RES / 2.0 - 1;
	myimg->sprite->y = 4.0 * RES + RES / 2.0 - 1;
	myimg->sprite->dist_to_sprite = sqrt(pow((myimg->play->x - myimg->sprite->x), 2.0) +
	pow((myimg->play->y - myimg->sprite->y), 2.0));
	myimg->sprite->trace = atan((myimg->sprite->y - myimg->play->y) / (myimg->sprite->x - myimg->play->x));
	trace = fix_angles(myimg);
	printf("%f\n%f\n", trace * 180.0 / PI, myimg->sprite->trace * 180.0 / PI);
	save = check_vision(myimg, trace);
	printf("%f\n", save);
//myimg->sprite->dis_mass[(int)(save / (PI / (3.0 * myimg->plane_x)))] > myimg->sprite->dist_to_sprite
	if (save != -1)
		draw_sprite(myimg, save);
}