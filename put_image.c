/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:37:06 by zcolleen          #+#    #+#             */
/*   Updated: 2020/07/25 17:43:18 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
//not in project

typedef struct p_img
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*mlx_img;
	char	*path_to_img;
	int		hight;
	int		width;
	int		coordinate;
}				s_img;

int		destroyer(s_img *data)
{
	data->mlx_img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
	return (0);
}

int		s_move(int keycode, s_img *data)
{
	if (keycode == 1)
	{
		data->coordinate+= 20;
		destroyer(data);
//		mlx_destroy_image(data->mlx_ptr, data->mlx_img);
		data->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, data->path_to_img, &(data->width), &(data->hight));
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, data->coordinate, data->coordinate);
	}
	return (0);
}

int main()
{
	s_img myimg;

	myimg.path_to_img = "./big.xpm";
	myimg.mlx_ptr = mlx_init();
	myimg.mlx_win = mlx_new_window(myimg.mlx_ptr, 1920, 1080, "testing png");
	myimg.mlx_img = mlx_xpm_file_to_image(myimg.mlx_ptr, myimg.path_to_img, &(myimg.width), &(myimg.hight));
	myimg.coordinate = 0;
	mlx_put_image_to_window(myimg.mlx_ptr, myimg.mlx_win, myimg.mlx_img, 0, 0);
//	printf("%d\n", myimg.width);
//	mlx_key_hook(myimg.mlx_win, s_move, &myimg);
	mlx_loop(myimg.mlx_ptr);
}