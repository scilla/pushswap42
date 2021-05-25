/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:25:36 by scilla            #+#    #+#             */
/*   Updated: 2021/05/25 15:25:37 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_t_stack(t_stack *stack)
{
	free(stack->data);
	free(stack);
}

void	free_register(t_stack **reg, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(reg[i]->data);
		free(reg[i]);
		i++;
	}
}

void	compare_lis(t_stack **reg, t_stack *dup, int stk_s_len)
{
	int	i;
	int	j;

	i = 1;
	while (i < dup->len)
	{
		j = 0;
		while (j < i)
		{
			if (dup->data[j] < dup->data[i] && reg[i]->len < reg[j]->len)
			{
				free(reg[i]->data);
				free(reg[i]);
				reg[i] = stack_dup(reg[j]->data, stk_s_len);
				reg[i]->len = reg[j]->len;
			}
			j++;
		}
		reg[i]->data[reg[i]->len] = dup->data[i];
		reg[i]->len++;
		i++;
	}
}

void	init_register(t_stack **reg, int dup_len, int stk_s_len)
{
	int	i;

	i = 0;
	while (i < stk_s_len)
	{
		reg[i] = malloc(sizeof(t_stack));
		reg[i]->data = malloc(sizeof(int) * (dup_len));
		reg[i]->len = 0;
		i++;
	}
}

void	ft_lis(t_stack *stk_s, t_stack **stk_d)
{
	t_stack	*dup;
	t_stack	**reg;
	int		i;

	dup = stack_dup(stk_s->data, stk_s->len);
	while (min_stack(dup) != dup->data[0])
		rotate(dup, dup);
	reg = (t_stack **)malloc(sizeof(t_stack *) * (dup->len));
	init_register(reg, dup->len, stk_s->len);
	reg[0]->data[0] = dup->data[0];
	reg[0]->len++;
	compare_lis(reg, dup, stk_s->len);
	i = max_stack(reg, dup->len);
	free_t_stack(*stk_d);
	*stk_d = stack_dup(reg[i]->data, reg[i]->len);
	free_register(reg, stk_s->len);
	free(reg);
	free_t_stack(dup);
}
