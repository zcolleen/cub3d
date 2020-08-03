/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:41:04 by zcolleen          #+#    #+#             */
/*   Updated: 2020/05/10 19:41:10 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *head;
	t_list *temp;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	head = *lst;
	temp = head;
	while (head != NULL)
	{
		head = head->next;
		del(temp->content);
		free(temp);
		temp = head;
	}
	*lst = NULL;
}
