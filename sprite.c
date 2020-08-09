/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 13:01:20 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/08 22:41:21 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	fix_angle(t_img *myimg, int col_hight)
{
	double	trace;
	double	angle;

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

void	draw_sprite(t_img *myimg, double trace, int col_hight, t_one_spr *point)
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
		if (myimg->sprite->dis_mass[x] > point->dist_to_sprite)
			draw_sprite_col(myimg, trace, x, col_hight);
//		printf(" x =  %d||", (int)((x - myimg->sprite->image_x) * (RES / col_hight)));
		x++;
	}
}

t_one_spr	*new_elem(int i, int j)
{
	t_one_spr *new;

	new = NULL;
	if (!(new = (t_one_spr *)malloc(sizeof(t_one_spr))))
		return (NULL);
	new->y = i * RES + RES / 2.0 - 1;
	new->x = j * RES + RES / 2.0 - 1;
	new->next = NULL;
	return (new);
}

int		put_elem_to_list(t_one_spr **head, int i, int j)
{
	t_one_spr *new;
	
	if (*head == NULL)
	{
		if ((*head = new_elem(i, j)) == NULL)
			return (-1);
		return (0);
	}
	else if (!(new = new_elem(i, j)))
		return (-1);
	new->next = *head;
	*head = new;
	return (0);
}

int		write_sprite(t_img *myimg)
{
	int i;
	int j;
	t_one_spr *head;

	i = 0;
	j = 0;
	head = NULL;
	while (myimg->reader->map[i] != NULL)
	{
		j = 0;
		while (myimg->reader->map[i][j] != '\0')
		{
			if (myimg->reader->map[i][j] == '2')
			{
				if (put_elem_to_list(&head, i, j) == -1)
					return (-1);
//				myimg->sprite->y = i * RES + RES / 2.0 - 1;
//				myimg->sprite->x = j * RES + RES / 2.0 - 1;
			}
			j++;
		}
		i++;
	}
	myimg->sprite->head = head;
	return (0);
}

void	sprite_trace(t_one_spr *point, t_img *myimg)
{
	if ((myimg->sprite->trace = atan((point->y - myimg->play->y) /
	(point->x - myimg->play->x))) < 0)
	{
		if ((point->y - myimg->play->y) < 0)
			myimg->sprite->trace =  myimg->sprite->trace + 2.0 * PI;
		else 
			myimg->sprite->trace =  myimg->sprite->trace + PI;
	}
	else
	{
		if ((point->x - myimg->play->x) < 0)
			myimg->sprite->trace = myimg->sprite->trace + PI;
	}
}

/*void	swap(t_one_spr **save, t_one_spr **point)
{
	(*save)->next = (*point)->next;
	(*point)->next = (*point)->next->next;
	(*save)->next->next = *point;
}
*/
void	swap(t_one_spr *first, t_one_spr *second, t_one_spr **head)
{
	t_one_spr *tmp;

	tmp = *head;
	if (first == *head)
	{
		first->next = second->next;
		second->next = *head;
		*head = second;
	}
	else
	{
		while (tmp->next != first)
			tmp = tmp->next;
		tmp->next = first->next;
		first->next = second->next;	
		second->next = first;	
	}
}

void	list_sort(t_one_spr **head)
{
	t_one_spr *tmp;
	int 		c;	

	c = 0;
	tmp = *head;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	while (c == 0)
	{
		tmp = *head;
		c = 1;
		while (tmp != NULL && tmp->next != NULL)
		{
			if (tmp->dist_to_sprite < tmp->next->dist_to_sprite)
			{
				swap(tmp, tmp->next, head);
				c = 0;
			}
			tmp = tmp->next;
		}
	}
}

void	sprite_drawer(t_img *myimg)
{
	double	trace;
	int		col_hight;
	double	proj_dist;
	t_one_spr *point;
	int		counter;

	counter = 0;
	proj_dist = (myimg->plane_x / 2.0) / tan(PI / 6.0);
	point = myimg->sprite->head;
	while (point != NULL)
	{//first most dist
		point->dist_to_sprite = sqrt(pow((myimg->play->x - point->x), 2.0) +
		pow((myimg->play->y - point->y), 2.0));
//		printf("x : %f y : %f\n", point->x, point->y);
//printf("%f\n", point->dist_to_sprite);
		point = point->next;
		counter++;
	}
//	exit (0);
	list_sort(&(myimg->sprite->head));
	point = myimg->sprite->head;
	while (point != NULL)
	{
		col_hight = (int)((((myimg->plane_y * proj_dist)) / 2.0) / (SCALE * point->dist_to_sprite));
		sprite_trace(point, myimg);
		trace = fix_angle(myimg, col_hight);
		if (trace != -1)
			draw_sprite(myimg, trace, col_hight, point);
		point = point->next;
	}
}