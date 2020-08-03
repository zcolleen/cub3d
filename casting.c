/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:18:09 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/02 19:03:08 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		intersect(char **map, double x, double y, t_img *myimg)
{
	// write(1, "\n", 1);
	// ft_putnbr_fd((int)(y / RES), 1);
	// write(1, "\n", 1);
	// ft_putnbr_fd((int)(x / RES), 1);
	// write(1, "\n", 1);
	int a;
	int b;

	a = (int)(y / RES);
	b = (int)(x / RES);
	// ft_putnbr_fd(myimg->play->max_y, 1);
	if (a < 0 || b < 0 || a >= myimg->play->max_y || b >= myimg->play->max_x[a])
		return (1);
	// write(1, &(map[(int)(y / RES)][(int)(x / RES)]), 1);
	if (map[a][b] == '1')//ограничить координаты
		return (1);
	return (0);
}

double		angle(double trace, int sw)
{
	if (sw == 1)
	{
		if (trace >= PI && trace <= 2 * PI)
			return (-1.0);
		else
			return (1.0);
	}
	else
	{
		if (((trace <= PI / 2.0) && (trace >= 0.0)) ||
		((trace >= 3 * PI / 2.0) && (trace <= 2 * PI)))
			return (1.0);
		else
			return (-1.0);
	}
}

double	trace_vert(char **map, t_img *myimg, double trace)
{
	double Ax;
	double Ay;
	double Xa;
	double Ya;

	if (((trace >= 3.0 * PI / 2.0) && (trace <= 2.0 * PI)) ||
	((trace <= PI / 2.0) && (trace >= 0)))
		Ax = ((int)(myimg->play->x / RES)) * RES + RES;
	else
		Ax = ((int)(myimg->play->x / RES)) * RES - 0.00001;
	Ay = myimg->play->y - (myimg->play->x - Ax) * tan(trace);
	Xa = angle(trace, 2) * RES;
	Ya = angle(trace, 2) * RES * tan(trace);
	while (intersect(map, Ax, Ay, myimg) != 1)
	{
		Ax = Ax + Xa;
		Ay = Ay + Ya;
	}
	myimg->text->square_coord_vert = Ay;
//	printf("vert_point : Ax = %f | Ay = %f\n", Ax, Ay);
	return (sqrt((pow((myimg->play->x - Ax), 2.0) +
	pow((myimg->play->y - Ay), 2.0))));
//	return (fabs((myimg->play->y - Ay) / sin(trace)));
}

double	trace_hor(char **map, t_img *myimg, double trace)
{
	double Ax;
	double Ay;
	double Xa;
	double Ya;

	if (trace >= PI && trace <= 2 * PI)
		Ay = ((int)((myimg->play->y / RES)) * RES) - 0.00001;
	else
		Ay = ((int)((myimg->play->y / RES)) * RES) + RES;
	Xa = angle(trace, 1) * RES / tan(trace);
	Ya = angle(trace, 1) * RES;
	Ax = myimg->play->x - (myimg->play->y - Ay) / tan(trace);
	while ((intersect(map, Ax, Ay, myimg)) != 1)
	{
		Ax = Ax + Xa;
		Ay = Ay + Ya;
	}
	myimg->text->square_coord_hor = Ax;
	// if (trace >= PI && trace <= 2 * PI)
	// 	myimg->text->square_coord_hor = (int)((int)(Ax / RES) * RES + RES - Ax); 
//	printf("hor_point : Ax = %f | Ay = %f\n", Ax, Ay);
//	return (fabs((myimg->play->y - Ay) / sin(trace)));
	return(sqrt((pow((myimg->play->x - Ax), 2.0) +
	pow((myimg->play->y - Ay), 2.0))));
}

int			undefault_angle(double trace)
{
	if (trace == PI / 2.0 || trace == 3.0 * PI / 2.0)
		return (1);
	if (trace == PI || trace == 2.0 * PI)
		return (2);
	return (0);
}

void		switch_texture(t_img *myimg, double trace, int sw)
{
	if (sw == 0)//вертикали
	{
		if (trace >= 0 && trace < PI)//юг
			myimg->text->flag = 4;
		else//север
			myimg->text->flag = 1;
	}
	else//горизонтали
	{
		if (trace >= PI / 2.0 && trace < 3.0 * PI / 2.0)//восток
			myimg->text->flag = 2;
		else//запад
			myimg->text->flag = 3;
	}
}

double		casting(char **map, t_img *myimg, double trace, double save_angle)
{
	double	distance1;
	double	distance2;
	double	save;

	save = save_angle - PI / 6.0 - trace;
	if (save > 2.0 * PI)
		save = save - 2.0 * PI;
	if (save < 0)
		save = save + 2.0 * PI;
	if (trace < 0)
		trace = trace + 2.0 * PI;
	if (trace > 2 * PI)
		trace = trace - 2 * PI;
//	printf("fixed angle: %f\n", trace / PI * 180.0);
	if (undefault_angle(trace) == 1)
	{
		distance1 = trace_hor(map, myimg, trace) * fabs(cos(save));
		switch_texture(myimg, trace, 1);
	}
	else if (undefault_angle(trace) == 2)
	{
		distance1 = trace_vert(map, myimg, trace) * fabs(cos(save));
		switch_texture(myimg, trace, 0);
	}
	else if ((distance1 = trace_vert(map, myimg, trace)) >=
	(distance2 = trace_hor(map, myimg, trace)))
	{
		distance1 = distance2 * fabs(cos(save));
		switch_texture(myimg, trace, 0);
	}
	else
	{
		distance1 = distance1 * fabs(cos(save));
		switch_texture(myimg, trace, 1);
	}
// * fabs(sin(trace))
//	printf("distance : %f\n", distance1);
	return (distance1);
}