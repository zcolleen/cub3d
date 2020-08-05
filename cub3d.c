/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:15:58 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/05 13:44:01 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		hooker(int keycode, t_img *myimg);
int		drawer(t_img *myimg);


double	starting_trace(t_img *myimg) 
{
	if (myimg->play->orientation == 1)
		return (4.0 * PI / 3.0);
	if (myimg->play->orientation == 2)
		return (PI / 3.0);
	if (myimg->play->orientation == 3)
		return (11.0 * PI / 6.0);
	if (myimg->play->orientation == 4)
		return (5.0 * PI / 6.0);
	return (0);
}

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

int		save_textures(t_img *myimg)
{
	t_north *north;
	t_west	*west;
	t_east	*east;
	t_south *south;

	if (!(north = (t_north*)malloc(sizeof(t_north))) || !(east = (t_east*)malloc(sizeof(t_east))) ||
	!(west = (t_west*)malloc(sizeof(t_west))) || !(south = (t_south*)malloc(sizeof(t_south))))
		return (-1);
	if (texturing(myimg) == -1)
		return (-1);
	north->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->text->path_to_north, &(north->width), &(north->hight));
	south->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->text->path_to_south, &(south->width), &(south->hight));
	west->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->text->path_to_west, &(west->width), &(west->hight));
	east->img = mlx_xpm_file_to_image(myimg->mlx_ptr, myimg->text->path_to_east, &(east->width), &(east->hight));
	north->addr = mlx_get_data_addr(north->img, &(north->bits_per_pixel), &(north->line_length), &(north->endian));
	west->addr = mlx_get_data_addr(west->img, &(west->bits_per_pixel), &(west->line_length), &(west->endian));
	south->addr = mlx_get_data_addr(south->img, &(south->bits_per_pixel), &(south->line_length), &(south->endian));
	east->addr = mlx_get_data_addr(east->img, &(east->bits_per_pixel), &(east->line_length), &(east->endian));
	myimg->north = north;
	myimg->west = west;
	myimg->east = east;
	myimg->south = south;
	return (0);
}

//  0xFFB6C1
// 0x00FF00

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
	f_c->cell_col = (f_c->red_c << 16) |  (f_c->green_c << 8) | (f_c->blue_c << 0);
	// printf("\n%d\n", f_c->cell_col);	
	// exit(0);
	f_c->floor_col = (f_c->red_f << 16) |  (f_c->green_f << 8) | (f_c->blue_f << 0);
	myimg->f_c = f_c;
	return (0);
}

int		starter(char **argv)//начало кода
{
	t_img *myimg;
	int i = 0;
	
	if (!(myimg = (t_img *)malloc(sizeof(t_img))))
		return (-1);
	// if (!(map = save_map(argv, myimg)))
	// 	return (-1);
	reader(myimg, argv);
	init(myimg->reader->map, myimg);
	if (init_sprite(myimg) == -1)
	 	return (-1);
	write_sprite(myimg);
//	flood_fill(myimg->reader->map, myimg, myimg->play->j, myimg->play->i);
	myimg->play->trace = starting_trace(myimg);
	myimg->map = myimg->reader->map;
	// while (myimg->map[i] != NULL)
	// {
	// 	printf("%sok\n", myimg->map[i]);
	// 	i++;
	// }
	
	if (save_textures(myimg) == -1 || save_f_c(myimg) == -1)
		return (-1);
	drawer(myimg);
	mlx_put_image_to_window(myimg->mlx_ptr, myimg->mlx_win, myimg->mlx_img, 0, 0);
	mlx_hook(myimg->mlx_win, 2, 0L, hooker, myimg);
	mlx_loop(myimg->mlx_ptr);
	return (0);
}

int		drawer(t_img *myimg)
{
	double	save;
	int		x;
	double	trace;
	double	dist;

	save = myimg->play->trace + PI / 3.0;
	trace = myimg->play->trace;
	x = 0;
	while (trace < save && x < myimg->plane_x)
	{
		// angle = (trace / PI) * 180;
		// printf("angle : %f = %f\n", trace, angle);
		dist = casting(myimg->map, myimg, trace, save);
		myimg->sprite->dis_mass[x] = dist;
		proector(dist, myimg, x, trace);
		//printf("\nplayers coordinate: %f - x %f - y\n", myimg->play->x, myimg->play->y);
		trace = (PI / 3.0) / myimg->plane_x + trace;
		x++;
	}
//	sprite_drawer(myimg);
	return (0);
}

int		hooker(int keycode, t_img *myimg)
{
	mlx_destroy_image(myimg->mlx_ptr, myimg->mlx_img);
	myimg->mlx_img = mlx_new_image(myimg->mlx_ptr, myimg->plane_x, myimg->plane_y);
	myimg->addr = mlx_get_data_addr(myimg->mlx_img, &(myimg->bits_per_pixel),
	&(myimg->line_length), &(myimg->endian));
	if (keycode == 123)
		myimg->play->trace = myimg->play->trace - (5 * PI) / myimg->plane_x;
	if (keycode == 124)
		myimg->play->trace = myimg->play->trace + (5 * PI) / myimg->plane_x;
	if (keycode == 13)
	{
		myimg->play->x = myimg->play->x + 3 * cos(myimg->play->trace + PI / 6.0);
		myimg->play->y = myimg->play->y + 3 * sin(myimg->play->trace + PI / 6.0);
	}
	if (keycode == 1)
	{
		myimg->play->x = myimg->play->x - 3 * cos(myimg->play->trace + PI / 6.0);
		myimg->play->y = myimg->play->y - 3 * sin(myimg->play->trace + PI / 6.0);
	}
	if (keycode == 0)
	{
		myimg->play->x = myimg->play->x + 3 * cos(myimg->play->trace + PI / 6.0 - PI / 2.0);
		myimg->play->y = myimg->play->y + 3 * sin(myimg->play->trace + PI / 6.0 - PI / 2.0);		
	}
	if (keycode == 2)
	{
		myimg->play->x = myimg->play->x - 3 * cos(myimg->play->trace + PI / 6.0 - PI / 2.0);
		myimg->play->y = myimg->play->y - 3 * sin(myimg->play->trace + PI / 6.0 - PI / 2.0);				
	}
	drawer(myimg);
	mlx_put_image_to_window(myimg->mlx_ptr, myimg->mlx_win, myimg->mlx_img, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		starter(argv);
	return (0);
}