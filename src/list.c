/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:11:52 by zcolleen          #+#    #+#             */
/*   Updated: 2020/08/11 18:05:11 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void		swap(t_one_spr *first, t_one_spr *second, t_one_spr **head)
{
	t_one_spr *tmp;

	tmp = *head;
	if (first == *head)
	{
		first->next = second->next;
		second->next = *head;
		*head = second;
	}
	else
	{
		while (tmp->next != first)
			tmp = tmp->next;
		tmp->next = first->next;
		first->next = second->next;
		second->next = first;
	}
}

void		list_sort(t_one_spr **head)
{
	t_one_spr	*tmp;
	int			c;

	c = 0;
	tmp = *head;
	if (*head == NULL || (*head)->next == NULL)
		return ;
	while (c == 0)
	{
		tmp = *head;
		c = 1;
		while (tmp != NULL && tmp->next != NULL)
		{
			if (tmp->dist_to_sprite < tmp->next->dist_to_sprite)
			{
				swap(tmp, tmp->next, head);
				c = 0;
			}
			tmp = tmp->next;
		}
	}
}
