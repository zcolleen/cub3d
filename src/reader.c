/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 19:15:29 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:39:46 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		writer(char c, t_img *myimg, char *path, int sw)
{
	if (sw == 0)
	{
		myimg->reader->path_to_sprite = path;
		myimg->reader->flag_sp = 1;
	}
	else
		writer_char(c, myimg, path);
	return (0);
}

int		allocator(char *line, t_img *myimg, char c, int sw)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (!(path = (char *)malloc(sizeof(char) * (i + 1))))
	{
		perror("Error");
		return (-1);
	}
	i = 0;
	while (line[i] != ' ' && line[i] != '\0')
	{
		path[i] = line[i];
		i++;
	}
	path[i] = '\0';
	return (writer(c, myimg, path, sw));
}

int		parcer(char *line, t_img *myimg, char c, int sw)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '.' && line[i + 1] == '/')
		return (allocator(line + i, myimg, c, sw));
	else
	{
		ft_putstr_fd("Error:\nwrong path\n", 1);
		return (-1);
	}
	return (0);
}

void	init_reader(t_img *myimg)
{
	myimg->reader->flag_e = 0;
	myimg->reader->flag_n = 0;
	myimg->reader->flag_s = 0;
	myimg->reader->flag_w = 0;
	myimg->reader->flag_sp = 0;
	myimg->reader->flag_cell = 0;
	myimg->reader->flag_floor = 0;
	myimg->reader->flag_res = 0;
	myimg->reader->flag_map = 0;
}

void	reader(t_img *myimg, char **argv)
{
	int			fd;
	t_reader	*reader;
	int			j;

	j = 0;
	if (!(reader = (t_reader*)malloc(sizeof(t_reader))))
		malloc_exit(myimg);
	myimg->reader = reader;
	init_reader(myimg);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		free(myimg->reader);
		free(myimg);
		perror("Error");
		exit(1);
	}
	myimg->skip = 0;
	get_l(fd, myimg, &j);
	alloc_map(argv, j, myimg, fd);
	path_parser(myimg);
	map_parser(myimg);
}
