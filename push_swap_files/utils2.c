#include "../push_swap.h"

int	min_in_arr(t_stack stack)
{
	int	min;
	int	i;

	min = stack.data[0];
	i = 0;
	while (stack.len--)
	{
		if (stack.data[stack.len] <= min)
		{
			i = stack.len;
			min = stack.data[stack.len];
		}
	}
	return (i);
}

int	max_in_arr(t_stack stack)
{
	int	max;
	int	i;

	max = stack.data[0];
	i = 0;
	while (stack.len--)
	{
		if (stack.data[stack.len] >= max)
		{
			i = stack.len;
			max = stack.data[stack.len];
		}
	}
	return (i);
}

int	check_in_lis(int value, t_stack *lis)
{
	int	i;

	i = 0;
	while (i < lis->len)
	{
		if (value == lis->data[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_inv_spot(t_stack *stk_b, int value)
{
	int	i;
	int	index_min;
	int	index_max;

	if (stk_b->len < 2)
		return (0);
	if (stk_b->data[stk_b->len - 1] < value && value < stk_b->data[0])
		return (0);
	index_min = min_in_arr(*stk_b);
	index_max = max_in_arr(*stk_b);
	if (value > stk_b->data[index_max] || value < stk_b->data[index_min])
		return (index_min);
	i = 0;
	while (i < stk_b->len - 1)
	{
		if (stk_b->data[i] < value && value < stk_b->data[i + 1])
			break ;
		i++;
	}
	return (i + 1);
}

int	find_spot(t_stack *stk_b, int value)
{
	int	i;
	int	index_min;
	int	index_max;

	if (stk_b->len < 2)
		return (0);
	if (stk_b->data[stk_b->len - 1] > value && value > stk_b->data[0])
		return (0);
	index_min = min_in_arr(*stk_b);
	index_max = max_in_arr(*stk_b);
	if (value > stk_b->data[index_max] || value < stk_b->data[index_min])
		return (index_max);
	i = 0;
	while (i < stk_b->len - 1)
	{
		if (stk_b->data[i] > value && value > stk_b->data[i + 1])
			break ;
		i++;
	}
	return (i + 1);
}
