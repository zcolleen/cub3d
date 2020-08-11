/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcearg_n_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:59:58 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:02:00 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	list_map_clear(t_img *myimg)
{
	t_one_spr	*tmp;
	t_one_spr	*save;
	int			i;

	i = 0;
	tmp = myimg->sprite->head;
	save = tmp;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		free(save);
		save = tmp;
	}
	while (myimg->map[i] != NULL)
	{
		free(myimg->map[i]);
		i++;
	}
	free(myimg->map);
}

void	all_free(t_img *myimg)
{
	mlx_destroy_image(myimg->mlx_ptr, myimg->mlx_img);
	free(myimg->play->max_x);
	free(myimg->play);
	free(myimg->text->path_to_east);
	free(myimg->text->path_to_north);
	free(myimg->text->path_to_south);
	free(myimg->text->path_to_west);
	free(myimg->text);
	free(myimg->east);
	free(myimg->south);
	free(myimg->west);
	free(myimg->north);
	free(myimg->f_c);
	free(myimg->reader);
	free(myimg->sprite->dis_mass);
	free(myimg->sprite->path_to_sprite);
	free(myimg->sprite);
	list_map_clear(myimg);
	free(myimg);
	exit(0);
}

void	parce_argv(char **argv)
{
	int fd;
	int i;

	fd = 0;
	i = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("Error");
		exit(1);
	}
	close(fd);
	while (argv[1][i] != '\0')
		i++;
	if (argv[1][i - 1] != 'b' || argv[1][i - 2] != 'u'
	|| argv[1][i - 3] != 'c' || argv[1][i - 4] != '.')
	{
		ft_putstr_fd("Error:\nnot a valid format\n", 1);
		exit(0);
	}
}

void	check_save(char **argv)
{
	if (argv[2][0] != '-' || argv[2][1] != '-'
	|| argv[2][2] != 's' || argv[2][3] != 'a' ||
	argv[2][4] != 'v' || argv[2][5] != 'e' || argv[2][6] != '\0')
	{
		ft_putstr_fd("Error:\nnot a valid argument\n", 1);
		exit(0);
	}
}
