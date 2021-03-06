/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 19:18:09 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 15:54:07 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int			intersect(char **map, double x, double y, t_img *myimg)
{
	int a;
	int b;

	a = (int)(y / RES);
	b = (int)(x / RES);
	if (a < 0 || b < 0 || a >= myimg->play->max_y || b >= myimg->play->max_x[a])
		return (1);
	if (map[a][b] == '1')
		return (1);
	return (0);
}

double		trace_vert(char **map, t_img *myimg, double trace)
{
	double ax;
	double ay;
	double xa;
	double ya;

	if (((trace >= 3.0 * PI / 2.0) && (trace <= 2.0 * PI)) ||
	((trace <= PI / 2.0) && (trace >= 0)))
		ax = ((int)(myimg->play->x / RES)) * RES + RES;
	else
		ax = ((int)(myimg->play->x / RES)) * RES - 0.0001;
	ay = myimg->play->y - (myimg->play->x - ax) * tan(trace);
	xa = angle(trace, 2) * RES;
	ya = angle(trace, 2) * RES * tan(trace);
	while (intersect(map, ax, ay, myimg) != 1)
	{
		ax = ax + xa;
		ay = ay + ya;
	}
	myimg->text->square_coord_vert = ay;
	return (sqrt((pow((myimg->play->x - ax), 2.0) +
	pow((myimg->play->y - ay), 2.0))));
}

double		trace_hor(char **map, t_img *myimg, double trace)
{
	double ax;
	double ay;
	double xa;
	double ya;

	if (trace >= PI && trace <= 2 * PI)
		ay = ((int)((myimg->play->y / RES)) * RES) - 0.0001;
	else
		ay = ((int)((myimg->play->y / RES)) * RES) + RES;
	xa = angle(trace, 1) * RES / tan(trace);
	ya = angle(trace, 1) * RES;
	ax = myimg->play->x - (myimg->play->y - ay) / tan(trace);
	while ((intersect(map, ax, ay, myimg)) != 1)
	{
		ax = ax + xa;
		ay = ay + ya;
	}
	myimg->text->square_coord_hor = ax;
	return (sqrt((pow((myimg->play->x - ax), 2.0) +
	pow((myimg->play->y - ay), 2.0))));
}

double		dist_compare(char **map, t_img *myimg, double trace, double save)
{
	double distance1;
	double distance2;

	if ((undefault_angle(trace) == 1) &&
	(distance1 = trace_hor(map, myimg, trace) * fabs(cos(save))))
		switch_texture(myimg, trace, 1);
	else if ((undefault_angle(trace) == 2) &&
	(distance1 = trace_vert(map, myimg, trace) * fabs(cos(save))))
		switch_texture(myimg, trace, 0);
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
	return (distance1);
}

double		casting(char **map, t_img *myimg, double trace, double save_angle)
{
	double	save;

	save = save_angle - PI / 6.0 - trace;
	while (save >= 2.0 * PI)
		save = save - 2.0 * PI;
	while (save < 0)
		save = save + 2.0 * PI;
	while (trace < 0)
		trace = trace + 2.0 * PI;
	while (trace >= 2 * PI)
		trace = trace - 2 * PI;
	return (dist_compare(map, myimg, trace, save));
}
