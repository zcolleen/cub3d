/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:27:34 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 18:05:05 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	hooker_fifth(int keycode, t_img *myimg)
{
	double play_x;
	double play_y;

	if (keycode == 2)
	{
		play_x = myimg->play->x - 3 *
		cos(myimg->play->trace + PI / 6.0 - PI / 2.0);
		play_y = myimg->play->y - 3 *
		sin(myimg->play->trace + PI / 6.0 - PI / 2.0);
		if (myimg->map[(int)(play_y / RES)][(int)(play_x / RES)] != '1')
		{
			myimg->play->x = play_x;
			myimg->play->y = play_y;
		}
	}
}

void	hooker_third(int keycode, t_img *myimg)
{
	double play_x;
	double play_y;

	if (keycode == 0)
	{
		play_x = myimg->play->x + 3 *
		cos(myimg->play->trace + PI / 6.0 - PI / 2.0);
		play_y = myimg->play->y + 3 *
		sin(myimg->play->trace + PI / 6.0 - PI / 2.0);
		if (myimg->map[(int)(play_y / RES)][(int)(play_x / RES)] != '1')
		{
			myimg->play->x = play_x;
			myimg->play->y = play_y;
		}
	}
	hooker_fifth(keycode, myimg);
	if (keycode == 53)
		all_free(myimg);
}

void	hooker_forth(int keycode, t_img *myimg)
{
	double play_x;
	double play_y;

	if (keycode == 1)
	{
		play_x = myimg->play->x - 3 *
		cos(myimg->play->trace + PI / 6.0);
		play_y = myimg->play->y - 3 *
		sin(myimg->play->trace + PI / 6.0);
		if (myimg->map[(int)(play_y / RES)][(int)(play_x / RES)] != '1')
		{
			myimg->play->x = play_x;
			myimg->play->y = play_y;
		}
	}
}

void	hooker_sec(int keycode, t_img *myimg)
{
	double play_x;
	double play_y;

	if (keycode == 13)
	{
		play_x = myimg->play->x + 3 *
		cos(myimg->play->trace + PI / 6.0);
		play_y = myimg->play->y + 3 *
		sin(myimg->play->trace + PI / 6.0);
		if (myimg->map[(int)(play_y / RES)][(int)(play_x / RES)] != '1')
		{
			myimg->play->x = play_x;
			myimg->play->y = play_y;
		}
	}
	hooker_forth(keycode, myimg);
}

int		hooker(int keycode, t_img *myimg)
{
	mlx_destroy_image(myimg->mlx_ptr, myimg->mlx_img);
	myimg->mlx_img = mlx_new_image(myimg->mlx_ptr,
	myimg->plane_x, myimg->plane_y);
	myimg->addr = mlx_get_data_addr(myimg->mlx_img, &(myimg->bits_per_pixel),
	&(myimg->line_length), &(myimg->endian));
	if (keycode == 123)
		myimg->play->trace = myimg->play->trace - (10 * PI) / myimg->plane_x;
	if (keycode == 124)
		myimg->play->trace = myimg->play->trace + (10 * PI) / myimg->plane_x;
	hooker_sec(keycode, myimg);
	hooker_third(keycode, myimg);
	drawer(myimg);
	mlx_put_image_to_window(myimg->mlx_ptr,
	myimg->mlx_win, myimg->mlx_img, 0, 0);
	return (0);
}
