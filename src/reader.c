/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 19:15:29 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 16:15:09 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

int		scip_digit(char *line)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int		check_line_f_c(char *line)
{
	if (*line == ',' && ft_isdigit(*(line + 1)))
		return (0);
	else
	{
		ft_putstr_fd("Error:\nbad color line\n", 1);
		return (-1);
	}
}

int		check_color(int i)
{
	if (i < 0 || i > 255)
		return (-1);
	return (0);
}

int		filler(char *line, int *i, int *j, int *k)
{
	if ((check_color(*i = ft_atoi(line))) == -1)
		return (-1);
	line = line + scip_digit(line);
	if (check_line_f_c(line) == 0)
		line++;
	else
		return (-1);
	if ((check_color(*j = ft_atoi(line))) == -1)
		return (-1);
	line = line + scip_digit(line);
	if (check_line_f_c(line) == 0)
		line++;
	else
		return (-1);
	if ((check_color(*k = ft_atoi(line))) == -1)
		return (-1);
	return (0);
}

int		allocator_f_c(char *line, t_img *myimg, char c)
{
	if (c == 'F')
	{
		myimg->reader->flag_floor = 1;
		return (filler(line, &(myimg->reader->r_f), &(myimg->reader->g_f),
		&(myimg->reader->b_f)));
	}
	if (c == 'C')
	{
		myimg->reader->flag_cell = 1;
		return (filler(line, &(myimg->reader->r_c), &(myimg->reader->g_c),
		&(myimg->reader->b_c)));
	}
	return (0);
}

int		parcer_f_c(char *line, t_img *myimg, char c)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (allocator_f_c(line + i, myimg, c));
	else
	{
		ft_putstr_fd("Error:\nwrong color line\n", 1);
		return (-1);
	}
}

int		check_line_res(char *line)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
		return (i);
	else
	{
		ft_putstr_fd("Error:\nbad resolution line\n", 1);
		return (-1);
	}
}

int		allocator_r(char *line, t_img *myimg)
{
	int i;

	myimg->reader->r_x = ft_atoi(line);
	if ((i = check_line_res(line)) == -1)
		return (-1);
	line = line + i;
	myimg->reader->r_y = ft_atoi(line);
	return (0);
}

int		parcer_r(char *line, t_img *myimg)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_isdigit(line[i]))
	{
		myimg->reader->flag_res = 1;
		return (allocator_r(line + i, myimg));
	}
	else
	{
		ft_putstr_fd("Error:\nbad resolution line\n", 1);
		return (-1);
	}
}

int		parce_line(t_img *myimg, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0' && line[i + 1] != '\0')
		i++;
	if (line[i] == 'S' && line[i + 1] != 'O' && !(myimg->reader->flag_sp))
		return (parcer(line + i + 1, myimg, line[i], 0));
	else if ((line[i] == 'N' && line[i + 1] == 'O' &&
	!(myimg->reader->flag_n)) ||
	(line[i] == 'S' && line[i + 1] == 'O' && !(myimg->reader->flag_s)) ||
	(line[i] == 'W' && line[i + 1] == 'E' && !(myimg->reader->flag_w))
	|| (line[i] == 'E' && line[i + 1] == 'A' && !(myimg->reader->flag_e)))
		return (parcer(line + i + 2, myimg, line[i], 1));
	else if (line[i] == 'F' && !(myimg->reader->flag_floor))
		return (parcer_f_c(line + i + 1, myimg, line[i]));
	else if (line[i] == 'C' && !(myimg->reader->flag_cell))
		return (parcer_f_c(line + i + 1, myimg, line[i]));
	else if (line[i] == 'R' && !(myimg->reader->flag_res))
		return (parcer_r(line + i + 1, myimg));
	else if (line[i] != ' ' && line[i] != '\0')
	{
		ft_putstr_fd("Error:\nbad line in file\n", 1);
		return (-1);
	}
	return (0);
}

int		check_for_elem(t_img *myimg)
{
	if (myimg->reader->flag_cell && myimg->reader->flag_floor &&
	myimg->reader->flag_e && myimg->reader->flag_n && myimg->reader->flag_s &&
	myimg->reader->flag_w && myimg->reader->flag_sp &&
	myimg->reader->flag_res)
		return (1);
	return (0);
}

void	check_follower(int follower, t_img *myimg, char *line)
{
	if (follower == -1)
	{
		cleaner(myimg);
		exit(1);
	}
	if (follower == 0 && check_for_elem(myimg) != 1)
	{
		free(line);
		cleaner(myimg);
		ft_putstr_fd("Error\nmissing element\n", 1);
		exit(0);
	}
}

void	get_l(int fd, t_img *myimg, int *j)
{
	int		follower;
	char	*line;

	while ((follower = get_next_line(fd, &line)) > 0)
	{
		if (parce_line(myimg, line) == -1)
		{
			cleaner(myimg);
			ft_putstr_fd("Error:\nwrong configuration", 1);
			exit(0);
		}
		myimg->skip++;
		free(line);
		if ((check_for_elem(myimg)) == 1)
			break ;
	}
	check_follower(follower, myimg, line);
	while ((follower = get_next_line(fd, &line)) > 0)
	{
		(*j)++;
		free(line);
	}
	if (ft_strlen(line))
		(*j)++;
	free(line);
}

int		check_for_valid_char(char c)
{
	if (c == ' ' || c == '\0' || c == '1' ||
	c == '2' || c == '0')
		return (1);
	if (c == 'S' || c == 'W' ||
	c == 'E' || c == 'N')
		return (0);
	return (-1);
}

void	clean_exit(t_img *myimg)
{
	cleaner(myimg);
	ft_putstr_fd("Error:\ninvalid char", 1);
	exit(0);
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
