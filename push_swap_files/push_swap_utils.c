/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:26:04 by scilla            #+#    #+#             */
/*   Updated: 2021/05/25 15:26:05 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	final_rotate(t_data *var, t_stack *stack_a)
{
	if (var->spot < stack_a->len / 2.0)
	{
		loop_move(var->spot, &rotate, stack_a, stack_a);
		print_moves(&(t_moves){var->spot, 0, 0, 1});
	}
	else
	{
		loop_move(stack_a->len - var->spot, &inv_rotate, stack_a, stack_a);
		print_moves(&(t_moves){stack_a->len - var->spot, 0, 0, 2});
	}
}

int	min_stack(t_stack *stack)
{
	int	i;
	int	res;

	res = stack->data[0];
	i = 0;
	while (i < stack->len)
	{
		if (stack->data[i] < res)
			res = stack->data[i];
		i++;
	}
	return (res);
}

int	max_stack(t_stack **stack, int len)
{
	int	i;
	int	res;
	int	max_ind;

	res = stack[0]->len;
	i = 0;
	while (i < len)
	{
		if (stack[i]->len > res)
		{
			res = stack[i]->len;
			max_ind = i;
		}
		i++;
	}
	return (max_ind);
}

t_stack	*stack_dup(int *data, int len)
{
	int		i;
	t_stack	*dst;

	dst = malloc(sizeof(t_stack));
	dst->data = malloc(sizeof(int) * len);
	dst->len = len;
	i = len;
	while (i > 0)
	{
		i--;
		dst->data[i] = data[i];
	}
	return (dst);
}
