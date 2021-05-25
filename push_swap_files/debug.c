/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:25:34 by scilla            #+#    #+#             */
/*   Updated: 2021/05/25 15:25:35 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_stack(t_stack *src)
{
	int	i;

	printf("stack len: %d\n", src->len);
	i = 0;
	while (i < src->len)
	{
		printf("%d\n", src->data[i]);
		i++;
	}
	printf("stack end\n");
}

int	check_lis(t_stack *stk_a, t_stack *stk_b, t_stack *lis)
{
	t_stack	*tmp;

	tmp = malloc(sizeof(t_stack));
	tmp->data = malloc(0);
	tmp->len = 0;
	push(stk_b, stk_a);
	ft_lis(stk_a, &tmp);
	if (tmp->len > lis->len)
	{
		free(lis->data);
		lis->data = tmp->data;
		lis->len = tmp->len;
		free(tmp);
		return (1);
	}
	push(stk_a, stk_b);
	free(tmp->data);
	free(tmp);
	return (0);
}

void	print_arr(t_list *stack_a, t_list *stack_b)
{
	if (stack_a)
	{
		printf("STACK A\n");
		while (stack_a)
		{
			printf("INDEX: %d		NUMBER: %d\n", stack_a->index, stack_a->nb);
			stack_a = stack_a->next;
		}
	}
	if (stack_b)
	{
		printf("STACK B\n");
		while (stack_b)
		{
			printf("INDEX: %d		NUMBER: %d\n", stack_b->index, stack_b->nb);
			stack_b = stack_b->next;
		}
	}
}
