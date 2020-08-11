/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:15:58 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:00:20 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

int		starter(char **argv)
{
	t_img *myimg;

	if (!(myimg = (t_img *)malloc(sizeof(t_img))))
		return (-1);
	reader(myimg, argv);
	if (init(myimg->reader->map, myimg, 0) == -1)
		return (-1);
	if (init_sprite(myimg) == -1)
		return (-1);
	if (write_sprite(myimg) == -1)
		return (-1);
	flood_fill(myimg->reader->map, myimg, myimg->play->j, myimg->play->i);
	myimg->play->trace = starting_trace(myimg);
	myimg->map = myimg->reader->map;
	if (save_textures(myimg) == -1 || save_f_c(myimg) == -1)
		return (-1);
	drawer(myimg);
	mlx_put_image_to_window(myimg->mlx_ptr,
	myimg->mlx_win, myimg->mlx_img, 0, 0);
	mlx_hook(myimg->mlx_win, 2, 0L, hooker, myimg);
	mlx_hook(myimg->mlx_win, 17, 0L, red_cross, myimg);
	mlx_loop(myimg->mlx_ptr);
	return (0);
}

int		red_cross(t_img *myimg)
{
	all_free(myimg);
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
		dist = casting(myimg->map, myimg, trace, save);
		myimg->sprite->dis_mass[x] = dist;
		proector(dist, myimg, x);
		trace = (PI / 3.0) / myimg->plane_x + trace;
		x++;
	}
	sprite_drawer(myimg);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		parce_argv(argv);
		if (starter(argv) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
	if (argc == 3)
	{
		check_save(argv);
		parce_argv(argv);
		if (starter_bmp(argv) == -1)
		{
			perror("Error");
			exit(1);
		}
	}
	else
	{
		ft_putstr_fd("Error:\nwrong number of arguments\n", 1);
		exit(0);
	}
}
