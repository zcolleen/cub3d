# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 14:14:15 by zcolleen          #+#    #+#              #
#    Updated: 2020/08/10 17:54:19 by zcolleen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SOURCE = src/bmp.c src/casting.c src/cub3d.c src/drowing.c src/init.c src/reader.c\
	src/sprite.c gnl/get_next_line.c gnl/get_next_line_utils.c

HEADER = cub.h

LIBFT = libft

FLAG_OBJ = -I . -I gnl/get_next_line.h -I /usr/local/include -c -Wall -Wextra -Werror

FLAG_LINK = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit $(LIBFT)/libft.a 

OBJ = $(SOURCE:.c=.o)


#cc -I /usr/local/include cub3d.c bmp.c casting.c drowing.c init.c sprite.c reader.c gnl/get_next_line.c gnl/get_next_line_utils.c libft/libft.a

#-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

%.o:%.c $(HEADER)
	gcc $(FLAG_OBJ) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make bonus -C $(LIBFT)
	gcc $(FLAG_LINK) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all
	