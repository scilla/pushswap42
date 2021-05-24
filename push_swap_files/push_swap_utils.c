#include "../push_swap.h"

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
