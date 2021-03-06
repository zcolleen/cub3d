# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 14:14:15 by zcolleen          #+#    #+#              #
#    Updated: 2020/08/11 18:14:31 by zcolleen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX_LIB = libmlx.dylib

MLX = mlx

SOURCE = src/bmp.c src/casting.c src/cub3d.c src/drowing.c src/init.c src/reader.c\
	src/sprite.c gnl/get_next_line.c gnl/get_next_line_utils.c src/hooker.c src/utils.c\
	src/reductor.c src/saver.c src/parcearg_n_free.c src/parce_sprite.c\
	src/list.c src/reader_2.c src/reader_3.c src/reader_4.c src/reader_5.c\
	src/reader_6.c

HEADER = cub.h

LIBFT = libft

FLAG_OBJ = -I . -I gnl/get_next_line.h -Imlx -c -Wall -Wextra -Werror

FLAG_LINK = -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT)/libft.a 

OBJ = $(SOURCE:.c=.o)

%.o:%.c $(HEADER)
	gcc $(FLAG_OBJ) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX)
	cp $(MLX)/$(MLX_LIB) ./
	make bonus -C $(LIBFT)
	gcc $(FLAG_LINK) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)
	rm -rf $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re