/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reductor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:45:58 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 15:54:19 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		switch_texture(t_img *myimg, double trace, int sw)
{
	if (sw == 0)
	{
		if (trace >= 0 && trace < PI)
			myimg->text->flag = 4;
		else
			myimg->text->flag = 1;
	}
	else
	{
		if (trace >= PI / 2.0 && trace < 3.0 * PI / 2.0)
			myimg->text->flag = 2;
		else
			myimg->text->flag = 3;
	}
}

double		angle(double trace, int sw)
{
	if (sw == 1)
	{
		if (trace >= PI && trace <= 2 * PI)
			return (-1.0);
		else
			return (1.0);
	}
	else
	{
		if (((trace <= PI / 2.0) && (trace >= 0.0)) ||
		((trace >= 3 * PI / 2.0) && (trace <= 2 * PI)))
			return (1.0);
		else
			return (-1.0);
	}
}

int			undefault_angle(double trace)
{
	if (trace == PI / 2.0 || trace == 3.0 * PI / 2.0)
		return (1);
	if (trace == PI || trace == 0)
		return (2);
	return (0);
}
