/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:38:59 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:40:56 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_dup(char **map, int fd, int j, t_img *myimg)
{
	char	*line;
	int		i;

	i = 0;
	while (myimg->skip-- > 0)
	{
		get_next_line(fd, &line);
		free(line);
	}
	while (j > 0)
	{
		get_next_line(fd, &line);
		if (!(map[i++] = ft_strdup(line)))
		{
			cleaner(myimg);
			perror("Error");
			free(map);
			exit(1);
		}
		free(line);
		j--;
	}
	myimg->reader->map = map;
	myimg->reader->flag_map = 1;
	close(fd);
}

void	alloc_map(char **argv, int j, t_img *myimg, int fd)
{
	char **map;

	if (!(map = (char **)malloc(sizeof(char *) * (j + 1))))
	{
		cleaner(myimg);
		perror("Error");
		exit(1);
	}
	map[j] = NULL;
	if (close(fd) == -1)
	{
		cleaner(myimg);
		free(map);
		perror("Error");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	map_dup(map, fd, j, myimg);
}

void	cleaner(t_img *myimg)
{
	int i;

	i = 0;
	if (myimg->reader->flag_e == 1)
		free(myimg->reader->path_to_east);
	if (myimg->reader->flag_n == 1)
		free(myimg->reader->path_to_north);
	if (myimg->reader->flag_w == 1)
		free(myimg->reader->path_to_west);
	if (myimg->reader->flag_s == 1)
		free(myimg->reader->path_to_south);
	if (myimg->reader->flag_sp == 1)
		free(myimg->reader->path_to_sprite);
	if (myimg->reader->flag_map == 1)
	{
		while (myimg->reader->map[i] != NULL)
		{
			free(myimg->reader->map[i]);
			i++;
		}
		free(myimg->reader->map);
	}
	free(myimg->reader);
	free(myimg);
}

void	writer_char(char c, t_img *myimg, char *path)
{
	if (c == 'N')
	{
		myimg->reader->path_to_north = path;
		myimg->reader->flag_n = 1;
	}
	else if (c == 'S')
	{
		myimg->reader->path_to_south = path;
		myimg->reader->flag_s = 1;
	}
	else if (c == 'E')
	{
		myimg->reader->path_to_east = path;
		myimg->reader->flag_e = 1;
	}
	else if (c == 'W')
	{
		myimg->reader->path_to_west = path;
		myimg->reader->flag_w = 1;
	}
}
