/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 13:01:20 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/08 13:10:39 by zcolleen         ###   ########.fr       */
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
//	printf("check first : %f, check second: %f\n", myimg->sprite->trace - trace + (PI / 3.0 / myimg->plane_x) * (col_hight), (myimg->sprite->trace - trace));
	if ((((myimg->sprite->trace - trace + (PI / 3.0 / myimg->plane_x) * (col_hight)) > 0) &&
	(myimg->sprite->trace - trace -  (PI / 3.0 / myimg->plane_x) * (col_hight)) < PI / 3.0) ||
	(trace - myimg->sprite->trace +  (PI / 3.0 / myimg->plane_x) * (col_hight)) > 5.0 * PI / 6.0)
	{
		if ((trace - myimg->sprite->trace +  (PI / 3.0 / myimg->plane_x) * (col_hight)) > 5.0 * PI / 6.0)
			return (2.0 * PI - trace + myimg->sprite->trace - (PI / 3.0 / myimg->plane_x) * (col_hight / 2.0));
		else
			return (myimg->sprite->trace - trace - (PI / 3.0 / myimg->plane_x) * (col_hight / 2.0));
		//- (PI / 3.0 / myimg->plane_x) * (col_hight / 2.0)

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


int		take_color_from_sprite(t_img *myimg, int x, int top_point, int col_hight)
{
	int		*data;
	int 	y;

	x = (int)((x - myimg->sprite->image_x) * (RES / col_hight));
//	printf("%d\n", x);
//	printf("%d\n", myimg->sprite->image_x);
	y = (int)((top_point - myimg->sprite->image_y) * (RES / col_hight));
// 	if (y < 0)
// 		y = 0;
// //	printf("%d\n", col_hight);
//	printf("%d\n", top_point - myimg->sprite->image_y);
	// printf(" x = %d || ", x);
//	printf("\n\n\n");
//	printf(" x = %d || ", x);
//	y = (int)(k * y);
	data = (int*)(myimg->sprite->addr + y * myimg->sprite->line_length + x * (myimg->sprite->bits_per_pixel / 8));
//	printf("%d\n", *data);
	return (*data);
}

void	draw_sprite_col(t_img *myimg, double save, int x, int col_hight)
{
	int		top_point;
	int		color;
	int i = 0;
	double	save_col;
	double	save_top;
// 	double	remainder;

// //	proj_dist = (myimg->plane_x / 2.0) / tan(PI / 6.0);
// 	remainder = 0;
	save_col = col_hight;
	save_top = (int)fabs((myimg->plane_y / 2.0) - (col_hight / 2.0));
//	myimg->sprite->image_y = save_top;
	if (col_hight > myimg->plane_y)
	{
		// remainder = col_hight - myimg->plane_y;
		col_hight = myimg->plane_y;
//		save_top = (int)((myimg->plane_y / 2.0) - (col_hight / 2.0)) + remainder;
	}
//	myimg->sprite->image_y = save_top;
//	save_col = col_hight;
//	save_top = (int)((myimg->plane_y / 2.0) - (col_hight / 2.0));// + remainder;
	top_point = (int)((myimg->plane_y / 2.0) - (col_hight / 2.0));
	myimg->sprite->image_y = top_point; //- remainder;
	col_hight = col_hight + top_point;
	while (top_point < col_hight)
	{
//		printf("%d\n", i);
		if ((color = take_color_from_sprite(myimg, x, save_top, save_col)) > 0)
			put_pixel(myimg, x, top_point, color);
	//	printf("%d\n", x);
//		printf("%d\n", top_point);
		top_point++;
		save_top++;
	}
	//printf("col hight %d = top point %d", col_hight, top_point);
//	exit (0);
}

void	draw_sprite(t_img *myimg, double trace, int col_hight)
{
	int		x;
	double	right_point;
	double	proj_dist;

	x = (int)((myimg->plane_x / (PI / 3.0)) * trace);
//	printf("x: %d\n", x);
	myimg->sprite->image_x = x;
	right_point = x + col_hight;
	if (right_point > myimg->plane_x)
		right_point = myimg->plane_x;
	if (x < 0)
		x = 0;
	while (x < right_point)
	{
		if (myimg->sprite->dis_mass[x] > myimg->sprite->dist_to_sprite)
			draw_sprite_col(myimg, trace, x, col_hight);
//		printf(" x =  %d||", (int)((x - myimg->sprite->image_x) * (RES / col_hight)));
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
//	printf("%f\n", myimg->sprite->dist_to_sprite);
//	exit (0);
	proj_dist = (myimg->plane_x / 2.0) / tan(PI / 6.0);
	col_hight = (int)((((myimg->plane_y * proj_dist)) / 2.0) / (SCALE * myimg->sprite->dist_to_sprite));
	sprite_trace(myimg);
	trace = fix_angle(myimg, col_hight);
//	printf("trace : %f\n", trace * 180.0 / PI);
//myimg->sprite->dis_mass[(int)(trace *  myimg->plane_x / (PI / 3.0))] > myimg->sprite->dist_to_sprite
//	printf("%f\n", myimg->sprite->dis_mass[(int)((trace) *  myimg->plane_x / (PI / 3.0))]);
	if (trace != -1)
		draw_sprite(myimg, trace, col_hight);
}