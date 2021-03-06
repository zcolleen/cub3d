/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:21:12 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 19:53:27 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# define PI 3.14159265358979323846
# define RES 64.0
# define PLANE_X 1920.0
# define PLANE_Y 1080.0
# define SCALE 16.0

# include "./gnl/get_next_line.h"
# include <fcntl.h>
# include "./libft/libft.h"
# include <stdio.h>
# include "mlx/mlx.h"
# include <math.h>

typedef	struct			s_one_spr
{
	struct s_one_spr	*next;
	double				x;
	double				y;
	double				dist_to_sprite;
}						t_one_spr;

typedef struct			s_sprite
{
	double				*dis_mass;
	double				dist_to_sprite;
	double				x;
	double				y;
	int					image_x;
	int					image_y;
	double				trace;
	void				*img;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				*addr;
	int					width;
	int					hight;
	char				*path_to_sprite;
	t_one_spr			*head;
}						t_sprite;

typedef struct			s_reader
{
	char				*path_to_north;
	char				*path_to_west;
	char				*path_to_east;
	char				*path_to_south;
	char				*path_to_sprite;
	int					r_c;
	int					g_c;
	int					b_c;
	int					r_f;
	int					g_f;
	int					b_f;
	int					r_x;
	int					r_y;
	int					flag_n;
	int					flag_s;
	int					flag_w;
	int					flag_e;
	int					flag_sp;
	int					flag_floor;
	int					flag_cell;
	int					flag_res;
	int					flag_map;
	char				**map;
}						t_reader;

typedef struct			s_east
{
	void				*img;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				*addr;
	int					width;
	int					hight;
}						t_east;

typedef struct			s_south
{
	void				*img;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				*addr;
	int					width;
	int					hight;
}						t_south;

typedef struct			s_west
{
	void				*img;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				*addr;
	int					width;
	int					hight;
}						t_west;

typedef struct			s_north
{
	void				*img;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				*addr;
	int					width;
	int					hight;
}						t_north;

typedef struct			s_play
{
	double				x;
	double				y;
	int					i;
	int					j;
	int					orientation;
	int					max_y;
	int					*max_x;
	double				trace;
}						t_play;

typedef struct			s_text
{
	char				*path_to_north;
	char				*path_to_west;
	char				*path_to_east;
	char				*path_to_south;
	char				*path_to_sprite;
	double				square_coord_vert;
	double				square_coord_hor;
	int					square_coord;
	double				flag;
}						t_text;

typedef struct			s_f_c
{
	int					floor_col;
	int					red_f;
	int					green_f;
	int					blue_f;
	int					red_c;
	int					green_c;
	int					blue_c;
	int					cell_col;
}						t_f_c;

typedef struct			s_img
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*mlx_img;
	int					bits_per_pixel;
	int					line_length;
	int					skip;
	int					endian;
	char				*addr;
	double				plane_x;
	double				plane_y;
	t_play				*play;
	t_text				*text;
	t_east				*east;
	t_north				*north;
	t_west				*west;
	t_south				*south;
	t_f_c				*f_c;
	t_reader			*reader;
	t_sprite			*sprite;
	char				**map;
}						t_img;

double					casting(char **map,
t_img *myimg, double trace, double save_angle);
void					proector(double distance, t_img *myimg, int x);
int						init(char **map, t_img *myimg, int sw);
void					reader(t_img *myimg, char **argv);
void					cleaner(t_img *myimg);
void					put_pixel(t_img *data, int x, int y, int color);
int						init_sprite(t_img *myimg);
void					sprite_drawer(t_img *myimg);
int						write_sprite(t_img *myimg);
void					flood_fill(char **map, t_img *myimg, int x, int y);
int						hooker(int keycode, t_img *myimg);
double					starting_trace(t_img *myimg);
int						save_textures(t_img *myimg);
int						save_f_c(t_img *myimg);
int						drawer(t_img *myimg);
int						starter_bmp(char **argv);
void					all_free(t_img *myimg);
void					cleaner(t_img *myimg);
int						hooker(int keycode, t_img *myimg);
int						drawer(t_img *myimg);
void					all_free(t_img *myimg);
void					list_map_clear(t_img *myimg);
int						red_cross(t_img *myimg);
int						hooker(int keycode, t_img *myimg);
void					split_bytes(int size, unsigned char *header);
void					switch_texture(t_img *myimg, double trace, int sw);
double					angle(double trace, int sw);
int						col_limit(int col_hight, t_img *myimg);
void					put_x_in_image(t_img *myimg);
void					player_coordinates(int i, int j,
t_img *data, int orient);
int						ft_isplayer(char c);
int						undefault_angle(double trace);
int						save_textures(t_img *myimg);
int						save_f_c(t_img *myimg);
void					check_save(char **argv);
void					parce_argv(char **argv);
void					all_free(t_img *myimg);
double					fix_angle(t_img *myimg, int col_hight);
int						write_sprite(t_img *myimg);
int						init_sprite(t_img *myimg);
void					malloc_exit(t_img *myimg);
void					path_parser(t_img *myimg);
void					map_parser(t_img *myimg);
void					list_sort(t_one_spr **head);
void					clean_exit(t_img *myimg);
int						check_for_valid_char(char c);
void					get_l(int fd, t_img *myimg, int *j);
void					check_follower(int follower, t_img *myimg, char *line);
int						check_for_elem(t_img *myimg);
int						parce_line(t_img *myimg, char *line);
int						parcer_f_c(char *line, t_img *myimg, char c);
int						check_line_res(char *line);
int						allocator_r(char *line, t_img *myimg);
int						parcer_r(char *line, t_img *myimg);
int						parce_line(t_img *myimg, char *line);
int						allocator_f_c(char *line, t_img *myimg, char c);
int						filler(char *line, int *i, int *j, int *k);
int						check_color(int i);
int						check_line_f_c(char *line);
int						scip_digit(char *line);
int						parcer(char *line, t_img *myimg, char c, int sw);
void					writer_char(char c, t_img *myimg, char *path);
void					cleaner(t_img *myimg);
void					alloc_map(char **argv, int j, t_img *myimg, int fd);

#endif
