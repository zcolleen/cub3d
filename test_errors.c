/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:50:56 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/01 23:42:36 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub.h"
#include <fcntl.h>
#include <mlx.h>

int main()
{
	// char *str;
	int fd;
	int width;
	int hight;
	void *ptr;
	void *win;
	void *img;

	// ptr = mlx_init();
	// win = mlx_new_window(ptr, 1920, 1080, "t");
	// img = mlx_xpm_file_to_image(ptr, "big.xpm", &hight, &width);
	perror("Error");
	// fd = open("map.cub", O_RDONLY);
	// perror("Error ");
	// str = strerror(errno);
	// perror("Error");
	// exit(0);
	// ft_putstr_fd("Error:\n", 1);
	// ft_putstr_fd(str, 1);
	// write(1, "\n", 1);
	return (0);
}