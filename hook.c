/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:51:33 by zcolleen          #+#    #+#             */
/*   Updated: 2020/07/31 20:35:01 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>

//not in project

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

/*
void	put_pixel(t_vars *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + y * data->line_length + x * (data->bits_per_pixel / 8);
	*(unsigned int*)dst = color;
}
*/

int		ft_close(int keycode, t_vars *var)
{
	if (keycode == 48)
		write(1, "ye", 2);
//	mlx_destroy_window(var->mlx, var->win);
	return (0);
}

int		print_pixel(int keycode, t_vars *var)
{
	write(1, "f", 1);
	return (0);
}

int main()
{
	t_vars var;
	int counter;

	counter = 0;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 1920, 1080, "Testing hooks");
	// mlx_key_hook(var.win, ft_close, &var);
//	while (counter++ < 10)
//		mlx_loop_hook(var.mlx, print_pixel, &var);
	mlx_loop(var.mlx);
}