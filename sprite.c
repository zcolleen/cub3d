/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 13:01:20 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/06 12:42:17 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	fix_angle(t_img *myimg, int col_hight)
{
	double trace;

	trace = myimg->play->trace;
	while (trace > 2 * PI)
		trace = trace - 2 * PI;
	while (trace <= 0)
		trace = trace + 2 * PI;
	printf("check first : %f, check second: %f\n", myimg->sprite->trace - trace + (PI / 3.0 / myimg->plane_x) * (col_hight), (myimg->sprite->trace - trace));
	if ((((myimg->sprite->trace - trace + (PI / 3.0 / myimg->plane_x) * (col_hight)) > 0) &&
	(myimg->sprite->trace - trace -  (PI / 3.0 / myimg->plane_x) * (col_hight)) < PI / 3.0) ||
	(trace - myimg->sprite->trace +  (PI / 3.0 / myimg->plane_x) * (col_hight)) > 5.0 * PI / 6.0)
	{
		if ((trace - myimg->sprite->trace +  (PI / 3.0 / myimg->plane_x) * (col_hight)) > 5.0 * PI / 6.0)
			return (2.0 * PI - trace + myimg->sprite->trace);
		else
			return (myimg->sprite->trace - trace);

//		printf("raznitsa : %f\n", myimg->sprite->trace - trace + (PI / 3.0 / myimg->plane_x) * (col_hight));
//		return (myimg->sprite->trace - trace);
	}
	else
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
	if (col_hight > myimg->plane_y)
		col_hight = myimg->plane_y;
	top_point = (myimg->plane_y / 2.0) - (col_hight / 2.0);
	col_hight = col_hight + top_point;
	while (top_point < col_hight)
	{
		put_pixel(myimg, x, top_point, 0x000000);
		top_point++;
	}
}

void	draw_sprite(t_img *myimg, double trace, int col_hight)
{
	int		x;
	double	right_point;
	double	proj_dist;

	x = (myimg->plane_x / (PI / 3.0)) * trace;
	printf("x: %d\n", x);
	right_point = x + col_hight;
	if (right_point > myimg->plane_x)
		right_point = myimg->plane_x;
	while (x < right_point)
	{
		if (x < 0)
			x = 0;
		draw_sprite_col(myimg, trace, x, col_hight);
		x++;
	}
}

void	write_sprite(t_img *myimg)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (myimg->reader->map[i] != NULL)
	{
		j = 0;
		while (myimg->reader->map[i][j] != '\0')
		{
			if (myimg->reader->map[i][j] == '2')
			{
				myimg->sprite->y = i * RES + RES / 2.0 - 1;
				myimg->sprite->x = j * RES + RES / 2.0 - 1;
			}
			j++;
		}
		i++;
	}
}

void	sprite_trace(t_img *myimg)
{
	if ((myimg->sprite->trace = atan((myimg->sprite->y - myimg->play->y) /
	(myimg->sprite->x - myimg->play->x))) < 0)
	{
		if ((myimg->sprite->y - myimg->play->y) < 0)
			myimg->sprite->trace =  myimg->sprite->trace + 2.0 * PI;
		else 
			myimg->sprite->trace =  myimg->sprite->trace + PI;
	}
	else
	{
		if ((myimg->sprite->x - myimg->play->x) < 0)
			myimg->sprite->trace = myimg->sprite->trace + PI;
	}
}

void	sprite_drawer(t_img *myimg)
{
	double	trace;
	int		col_hight;
	double	proj_dist;

	myimg->sprite->dist_to_sprite = sqrt(pow((myimg->play->x - myimg->sprite->x), 2.0) +
	pow((myimg->play->y - myimg->sprite->y), 2.0));
	proj_dist = (myimg->plane_x / 2.0) / tan(PI / 6.0);
	col_hight = (int)((((myimg->plane_y * proj_dist)) / 2.0) / (SCALE * myimg->sprite->dist_to_sprite));
	sprite_trace(myimg);
	trace = fix_angle(myimg, col_hight);
//	printf("trace : %f = trace : %f ||  sprite trace: %f\n", trace, trace * 180.0 / PI, myimg->sprite->trace * 180.0 / PI);
//myimg->sprite->dis_mass[(int)(save / (PI / (3.0 * myimg->plane_x)))] > myimg->sprite->dist_to_sprite
	if (trace != -1)
		draw_sprite(myimg, trace, col_hight);
}