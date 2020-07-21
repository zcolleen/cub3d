/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:51:33 by zcolleen          #+#    #+#             */
/*   Updated: 2020/07/21 22:28:41 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;


int		ft_close(int keycode, t_vars *var)
{
	write(1, "ye", 2);
//	mlx_destroy_window(var->mlx, var->win);
	return (0);
}

int main()
{
	t_vars var;

	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 1920, 1080, "Testing hooks");
	mlx_key_hook(var.win, ft_close, &var);
	mlx_loop(var.mlx);
}