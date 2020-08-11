/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:14:35 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:18:08 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_parser(t_img *myimg)
{
	int i;
	int j;
	int save;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	save = 0;
	while (myimg->reader->map[i] != NULL)
	{
		j = 0;
		while (myimg->reader->map[i][j] != '\0')
		{
			if ((save = check_for_valid_char(myimg->reader->map[i][j])) > 0 ||
			(save == 0 && flag == 0))
				j++;
			else
				clean_exit(myimg);
			if (save == 0)
				flag = 1;
		}
		i++;
	}
}

void	closer(int j, int k, int c, int b)
{
	close(j);
	close(k);
	close(c);
	close(b);
}

void	path_parser(t_img *myimg)
{
	int fd1;
	int fd2;
	int fd3;
	int fd4;
	int fd5;

	fd1 = 0;
	fd2 = 0;
	fd3 = 0;
	fd4 = 0;
	fd5 = 0;
	if ((fd1 = open(myimg->reader->path_to_east, O_RDONLY)) < 0 ||
	(fd2 = open(myimg->reader->path_to_north, O_RDONLY)) < 0 ||
	(fd3 = open(myimg->reader->path_to_south, O_RDONLY)) < 0 ||
	(fd4 = open(myimg->reader->path_to_sprite, O_RDONLY)) < 0 ||
	(fd5 = open(myimg->reader->path_to_west, O_RDONLY)) < 0)
	{
		close(fd1);
		closer(fd2, fd3, fd4, fd5);
		cleaner(myimg);
		ft_putstr_fd("Error:\ninvalid path\n", 1);
		exit(0);
	}
	close(fd1);
	closer(fd2, fd3, fd4, fd5);
}

void	malloc_exit(t_img *myimg)
{
	free(myimg);
	perror("Error");
	exit(1);
}
