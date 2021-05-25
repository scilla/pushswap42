/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:25:57 by scilla            #+#    #+#             */
/*   Updated: 2021/05/25 15:25:58 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rr(t_stack *stk_a, t_stack *stk_b)
{
	rotate(stk_a, stk_a);
	rotate(stk_b, stk_b);
}

void	rrr(t_stack *stk_a, t_stack *stk_b)
{
	inv_rotate(stk_a, stk_a);
	inv_rotate(stk_b, stk_b);
}

void	push(t_stack *stk_s, t_stack *stk_d)
{
	int	*new_src;
	int	*new_dst;
	int	i;

	if (!stk_s->len)
		return ;
	new_src = malloc(sizeof(int) * (stk_s->len - 1));
	new_dst = malloc(sizeof(int) * (stk_d->len + 1));
	new_dst[0] = stk_s->data[0];
	i = stk_s->len;
	while (i-- > 1)
		new_src[i - 1] = stk_s->data[i];
	i = stk_d->len;
	while (i > 0)
	{
		new_dst[i] = stk_d->data[i - 1];
		i--;
	}
	free(stk_s->data);
	free(stk_d->data);
	stk_s->data = new_src;
	stk_d->data = new_dst;
	stk_d->len++;
	stk_s->len--;
}
