/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_loc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 14:47:36 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/02 18:33:32 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	player_coordinates(int i, int j, t_img *data, int orient)
{
	data->play->x = j * RES + RES / 2 - 1;
	data->play->y = i * RES + RES / 2 - 1;
	data->play->orientation = orient;
}

int		ft_isplayer(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (2);
	if (c == 'E')
		return (3);
	if (c == 'W')
		return (4);
	return (0);
}

void	search_for_player(char **map, t_img *data)
{
	int i;
	int j;
	int orient;

	i = 0;
	j = 0;
	orient = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if ((orient = ft_isplayer(map[i][j])) != 0)
				player_coordinates(i, j, data, orient);
			j++;
		}
		i++;
	}
	data->play->max_y = i;
}

void	window_init(t_img *myimg)
{
	myimg->plane_x = myimg->reader->r_x;
	myimg->plane_y = myimg->reader->r_y;
	myimg->mlx_ptr = mlx_init();
	myimg->mlx_win = mlx_new_window(myimg->mlx_ptr, myimg->plane_x, myimg->plane_y, "cub3d");
	myimg->mlx_img = mlx_new_image(myimg->mlx_ptr, myimg->plane_x, myimg->plane_y);
	myimg->addr = mlx_get_data_addr(myimg->mlx_img, &(myimg->bits_per_pixel),
	&(myimg->line_length), &(myimg->endian));
}

int		init(char **map, t_img *myimg)
{
	t_play	*play;
	int		*max_x;
	int		i;

	i = 0;
	if (!(play = (t_play *)malloc(sizeof(t_play))))
		return (-1);
	window_init(myimg);
	myimg->play = play;
	search_for_player(map, myimg);
	if (!(max_x = (int *)malloc(sizeof(int) * myimg->play->max_y)))
		return (-1);
	while (map[i] != NULL)
	{
		max_x[i] = ft_strlen(map[i]);
		i++;
	}
	myimg->play->max_x = max_x;
	return (0);
}