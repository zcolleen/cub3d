/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saver.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:56:13 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 15:58:21 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		texturing(t_img *myimg)
{
	t_text	*text;

	if (!(text = (t_text *)malloc(sizeof(t_text))))
		return (-1);
	text->path_to_north = myimg->reader->path_to_north;
	text->path_to_east = myimg->reader->path_to_east;
	text->path_to_south = myimg->reader->path_to_south;
	text->path_to_west = myimg->reader->path_to_west;
	myimg->text = text;
	return (0);
}

void	get_data_textures(t_north *north, t_west *west,
t_south *south, t_img *myimg)
{
	north->img = mlx_xpm_file_to_image(myimg->mlx_ptr,
	myimg->text->path_to_north,
	&(north->width), &(north->hight));
	south->img = mlx_xpm_file_to_image(myimg->mlx_ptr,
	myimg->text->path_to_south,
	&(south->width), &(south->hight));
	west->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->text->path_to_west,
	&(west->width), &(west->hight));
	north->addr = mlx_get_data_addr(north->img, &(north->bits_per_pixel),
	&(north->line_length), &(north->endian));
	west->addr = mlx_get_data_addr(west->img, &(west->bits_per_pixel),
	&(west->line_length), &(west->endian));
	south->addr = mlx_get_data_addr(south->img, &(south->bits_per_pixel),
	&(south->line_length), &(south->endian));
}

int		save_textures(t_img *myimg)
{
	t_north *north;
	t_west	*west;
	t_east	*east;
	t_south *south;

	if (!(north = (t_north*)malloc(sizeof(t_north))) ||
	!(east = (t_east*)malloc(sizeof(t_east))) ||
	!(west = (t_west*)malloc(sizeof(t_west))) ||
	!(south = (t_south*)malloc(sizeof(t_south))))
		return (-1);
	if (texturing(myimg) == -1)
		return (-1);
	get_data_textures(north, west, south, myimg);
	east->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->text->path_to_east,
	&(east->width), &(east->hight));
	east->addr = mlx_get_data_addr(east->img, &(east->bits_per_pixel),
	&(east->line_length), &(east->endian));
	myimg->north = north;
	myimg->west = west;
	myimg->east = east;
	myimg->south = south;
	return (0);
}

int		save_f_c(t_img *myimg)
{
	t_f_c *f_c;

	if (!(f_c = (t_f_c*)malloc(sizeof(t_f_c))))
		return (-1);
	f_c->red_c = myimg->reader->r_c;
	f_c->green_c = myimg->reader->g_c;
	f_c->blue_c = myimg->reader->b_c;
	f_c->red_f = myimg->reader->r_f;
	f_c->green_f = myimg->reader->g_f;
	f_c->blue_f = myimg->reader->b_f;
	f_c->cell_col = (f_c->red_c << 16) |
	(f_c->green_c << 8) | (f_c->blue_c << 0);
	f_c->floor_col = (f_c->red_f << 16) |
	(f_c->green_f << 8) | (f_c->blue_f << 0);
	myimg->f_c = f_c;
	return (0);
}
