/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:37:49 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/05/11 14:20:56 by vbuonvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if(!(*lst))
		*lst = ft_lstnew(new->nb, 1);
	else
	{
		(*lst)->previous = new;
		new->next = *lst;
		//new->index = 1;
		new->previous = NULL;
		*lst = new;
	}
}
