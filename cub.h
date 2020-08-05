/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:21:12 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/05 13:16:49 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define PI 3.14159265358979323846
# define RES 64.0
# define PLANE_X 1920.0
# define PLANE_Y 1080.0
# define SCALE 32.0

#include "./gnl/get_next_line.h"
#include <fcntl.h>
#include "./libft/libft.h"
#include <stdio.h>
#include <mlx.h>
#include <math.h>

typedef struct	s_sprite
{
	double		*dis_mass;
	double		dist_to_sprite;
	double		x;
	double		y;
	double		trace;
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	int			width;
	int			hight;
	char		*path_to_sprite;
}				t_sprite;

typedef struct	s_reader 
{
	char	*path_to_north;
	char	*path_to_west;
	char	*path_to_east;
	char	*path_to_south;
	char	*path_to_sprite;
	int		r_c;
	int		g_c;
	int		b_c;
	int		r_f;
	int		g_f;
	int		b_f;
	int		r_x;
	int 	r_y;
	int		flag_n;
	int		flag_s;
	int		flag_w;
	int		flag_e;
	int 	flag_sp;
	int		flag_floor;
	int		flag_cell;
	int		flag_res;
	int 	flag_map;
	char	**map;
}				t_reader;


typedef struct	s_east
{
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	int			width;
	int			hight;
}				t_east;

typedef struct	s_south
{
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	int			width;
	int			hight;
}				t_south;

typedef struct	s_west
{
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	int			width;
	int			hight;
}				t_west;

typedef struct	s_north
{
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	int			width;
	int			hight;
}				t_north;

typedef struct	s_play
{
	double		x;
	double		y;
	int 		i;
	int 		j;
	int			orientation;
	int			max_y;
	int			*max_x;
	double		trace;
}				t_play;

typedef struct	s_text
{
	char	*path_to_north;
	char	*path_to_west;
	char	*path_to_east;
	char	*path_to_south;
	char	*path_to_sprite;
	double	square_coord_vert;
	double	square_coord_hor;
	int		square_coord;
	double	flag;
}				t_text;

typedef struct	s_f_c
{
	int		floor_col;
	int		red_f;
	int		green_f;
	int		blue_f;
	int 	red_c;
	int 	green_c;
	int 	blue_c;
	int		cell_col;
}				t_f_c;

typedef struct	s_img
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*addr;
	double		plane_x;
	double		plane_y;
	t_play		*play;
	t_text		*text;
	t_east		*east;
	t_north		*north;
	t_west		*west;
	t_south		*south;
	t_f_c		*f_c;
	t_reader	*reader;
	t_sprite	*sprite;
	char		**map;
}				t_img;

double		casting(char **map, t_img *myimg, double trace, double save_angle);
void		proector(double distance, t_img *myimg, int x, double angle);
int			init(char **map, t_img *myimg);
void		reader(t_img *myimg, char **argv);
void		cleaner(t_img *myimg);
void		put_pixel(t_img *data, int x, int y, int color);
int			init_sprite(t_img *myimg);
void		sprite_drawer(t_img *myimg);
void		write_sprite(t_img *myimg);
void		flood_fill(char **map, t_img *myimg, int x, int y);



#endif