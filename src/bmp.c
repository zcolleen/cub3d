/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 15:35:05 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 15:43:53 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	header(t_img *myimg, unsigned int image_size, int fd)
{
	unsigned char	header[54];
	unsigned int	i;

	i = 0;
	while (i++ < 54)
		header[i] = (unsigned char)0;
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	split_bytes(image_size, header + 2);
	split_bytes(54, header + 10);
	split_bytes(40, header + 14);
	split_bytes(myimg->plane_x, header + 18);
	split_bytes(myimg->plane_y, header + 22);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, &header, 54);
}

int		*get_color_bmp(t_img *data, int y, int x)
{
	int *dst;

	dst = (int *)(data->addr + ((int)data->plane_y - y) * data->line_length +
	x * (data->bits_per_pixel / 8));
	return (dst);
}

void	save_image(t_img *myimg, int fd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < myimg->plane_y)
	{
		j = 0;
		while (j < myimg->plane_x)
		{
			write(fd, get_color_bmp(myimg, i, j), 3);
			j++;
		}
		i++;
	}
}

void	saver_bmp(t_img *myimg)
{
	int				fd;
	unsigned int	image_size;

	image_size = myimg->plane_x * myimg->plane_y * 4 + 54;
	fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	header(myimg, image_size, fd);
	save_image(myimg, fd);
}

int		starter_bmp(char **argv)
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
	saver_bmp(myimg);
	all_free(myimg);
	return (0);
}
