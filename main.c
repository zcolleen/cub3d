/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:27:57 by zcolleen          #+#    #+#             */
/*   Updated: 2020/07/25 16:32:18 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

//not in project

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;;
	int			endian;
}				t_data;


void	put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + y * data->line_length + x * (data->bits_per_pixel / 8);
	*(unsigned int*)dst = color;
}


void square(t_data *data, int x, int y, int color, int side)
{
	int counter;
	int coordinatex;
	int coordinatey;

	counter = 0;
	while (counter++ < side)
	{
		put_pixel(data, x + counter, y, color);
		put_pixel(data, x, y + counter, color);
	}
	coordinatex = x + counter;
	coordinatey = y + counter;
	counter = 0;
	while (counter++ < side)
	{
		put_pixel(data, x + counter, coordinatey, color);
		put_pixel(data, coordinatex, y + counter, color);
	}
}

int main(void)
{
	void *mlx_ptr;
	t_data *img;
	void *mlx_win;
	int x;
	int y;
	int z;

	x = 100;
	y = 100;
	z = 0;
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 10000, 10000, "Hello wold!");
	img->img = mlx_new_image(mlx_ptr, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length), &(img->endian));
	square(img, 100, 100, 0x90FF0000, 200);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img->img, 0, 0);
	mlx_loop(mlx_ptr);
}