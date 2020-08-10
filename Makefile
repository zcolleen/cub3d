# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 14:14:15 by zcolleen          #+#    #+#              #
#    Updated: 2020/08/10 16:22:48 by zcolleen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SOURCE = src/bmp.c src/casting.c src/cub3d.c src/drowing.c src/init.c src/reader.c\
	src/sprite.c gnl/get_next_line.c gnl/get_next_line_utils.c

HEADER = cub.h

LIBFT = libft

MINILIB = minilibx

OBJ = $(SOURCE:.c=.o)

FLAG_OBJ = -c -Wall -Wextra -Werror -I. -I /usr/local/include -I gnl/get_next_line.h

FLAG_LINK = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit $(LIBFT)/libft.a -o

%.o:%.c
	$(CC) $(FLAGS_OBJ) $<

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make bonus -C $(LIBFT)
	make -C $(MINILIB)
	$(CC) $(FLAG_LINK) $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT)
	rm -f minilibx/*.o
	