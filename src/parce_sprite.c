/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:06:37 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 18:05:16 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

double		fix_angle(t_img *myimg, int col_hight)
{
	double	trace;

	trace = myimg->play->trace;
	while (trace > 2 * PI)
		trace = trace - 2 * PI;
	while (trace <= 0)
		trace = trace + 2 * PI;
	if ((((myimg->sprite->trace - trace +
	(PI / 3.0 / myimg->plane_x) * (col_hight)) > 0) &&
	(myimg->sprite->trace - trace -
	(PI / 3.0 / myimg->plane_x) * (col_hight)) < PI / 3.0) ||
	(trace - myimg->sprite->trace +
	(PI / 3.0 / myimg->plane_x) * (col_hight)) > 5.0 * PI / 6.0)
	{
		if ((trace - myimg->sprite->trace +
		(PI / 3.0 / myimg->plane_x) * (col_hight)) > 5.0 * PI / 6.0)
			return (2.0 * PI - trace + myimg->sprite->trace -
			(PI / 3.0 / myimg->plane_x) * (col_hight / 2.0));
		else
			return (myimg->sprite->trace - trace -
			(PI / 3.0 / myimg->plane_x) * (col_hight / 2.0));
	}
	else
		return (-1);
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

int			put_elem_to_list(t_one_spr **head, int i, int j)
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

int			write_sprite(t_img *myimg)
{
	int			i;
	int			j;
	t_one_spr	*head;

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
			}
			j++;
		}
		i++;
	}
	myimg->sprite->head = head;
	return (0);
}

int			init_sprite(t_img *myimg)
{
	t_sprite *sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		return (-1);
	if (!(sprite->dis_mass = (double *)malloc(sizeof(double) * myimg->plane_x)))
		return (-1);
	myimg->sprite = sprite;
	myimg->sprite->path_to_sprite = myimg->reader->path_to_sprite;
	myimg->sprite->img = mlx_xpm_file_to_image(myimg->mlx_ptr,
	myimg->sprite->path_to_sprite,
	&(myimg->sprite->width), &(myimg->sprite->hight));
	myimg->sprite->addr = mlx_get_data_addr(myimg->sprite->img,
	&(myimg->sprite->bits_per_pixel), &(myimg->sprite->line_length),
	&(myimg->sprite->endian));
	return (0);
}
