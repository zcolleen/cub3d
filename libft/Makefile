# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcolleen <zcolleen@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 15:55:50 by zcolleen          #+#    #+#              #
#    Updated: 2020/05/14 18:48:08 by zcolleen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCE = ft_isascii.c ft_isalpha.c ft_memccpy.c ft_memset.c ft_split.c ft_strlcpy.c\
	ft_strrchr.c ft_atoi.c ft_memchr.c ft_putchar_fd.c ft_strchr.c\
	ft_strlen.c ft_strtrim.c ft_bzero.c ft_isdigit.c ft_memcmp.c ft_putendl_fd.c\
	ft_strdup.c ft_strmapi.c ft_substr.c ft_calloc.c ft_isprint.c ft_memcpy.c\
  	ft_putnbr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c ft_isalnum.c ft_itoa.c\
	ft_memmove.c ft_putstr_fd.c ft_strlcat.c ft_strnstr.c ft_toupper.c 	

SOURCE_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstiter.c\
	       ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c

HEADER = libft.h

OBJECT = $(SOURCE:c=o)

OBJECT_BONUS = $(SOURCE_BONUS:c=o)

FLAGS = -c -Wall -Wextra -Werror -I.

ifdef WITH_BONUS
OBJECT_FILES = $(OBJECT) $(OBJECT_BONUS)
else
OBJECT_FILES = $(OBJECT)
endif

%.o:%.c
	gcc $(FLAGS) $<

all: $(NAME)

$(NAME): $(OBJECT_FILES) $(HEADER)	
		ar rc $(NAME) $(OBJECT_FILES)
		ranlib $(NAME)

clean: 
		rm -f $(OBJECT)
		rm -f $(OBJECT_BONUS)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus: 
	$(MAKE) WITH_BONUS=1 all
