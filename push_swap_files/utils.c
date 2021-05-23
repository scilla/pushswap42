#include "../push_swap.h"
// 0 A+ B+   1 A+ B-   2 A- B+   3 A- B-


int	min_in_arr(t_stack stack)
{
	int min;
	int i;

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
	int max;
	int i;

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

	//	printf("cil %d %d %d\n", value, lis->data[i], lis->len);
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
			break;
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
			break;
		i++;
	}
	return (i + 1);
}

void	check_stack(t_stack *stack, char *dir)
{
	if (!ft_strcmp(dir, "cre"))
	{
		for (int i = 0; i < stack->len - 1; i++)
		{
			if (stack->data[i] > stack->data[i + 1])
			{
				printf("Hai cannato scemo\n");
				return ;
			}
		}
	}
	else if (!ft_strcmp(dir, "dec"))
	{
		for (int i = 0; i < stack->len - 1; i++)
		{
			if (stack->data[i] < stack->data[i + 1])
			{
				printf("Hai cannato scemo\n");
				return ;
			}
		}
	}
	printf("Ti e' andata bene\n");
}

t_moves	*count_moves(int index_a, int index_b, int len_a,  int len_b)
{
	t_moves	*curr;
	int 	k;

	curr = malloc(sizeof(t_moves));
	curr->abs_moves = 9999;
	k = index_b;
	if (index_a > index_b)
		k = index_a;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = index_a;
		curr->moves_b = index_b;
		curr->opt_code = 0;
	}
	k = len_b - index_b;
	if (len_a - index_a > len_b - index_b)
		k = len_a - index_a;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = len_a - index_a;
		curr->moves_b = len_b - index_b;
		curr->opt_code = 3;
	}
	k = index_a + len_b - index_b;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = index_a;
		curr->moves_b = len_b - index_b;
		curr->opt_code = 1;
	}
	k = len_a -index_a + index_b;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = len_a - index_a;
		curr->moves_b = index_b;
		curr->opt_code = 2;
	}
	return (curr);
}

t_moves	*predict_moves(t_stack *stk_a, t_stack *stk_b, t_stack *lis)
{
	int		i;
	int		index_b;
	t_moves	*best;
	t_moves	*curr;

	i = 0;
	best = malloc(sizeof(t_moves));
	best->abs_moves = 9999;
	while (i < stk_a->len)
	{
		
		//printf("protect? %d %d %d\n", stk_a->data[i], i, check_in_lis(stk_a->data[i], lis));
		if (check_in_lis(stk_a->data[i], lis))
		{
			i++;
			continue ;
		}
		index_b = find_spot(stk_b, stk_a->data[i]);
		curr = count_moves(i, index_b, stk_a->len, stk_b->len);
		if (curr->abs_moves < best->abs_moves)
		{
			free(best);
			best = curr;
		}
		i++;
	}
	return (best);
}

void loop_print(char *cmd, int nb)
{
	while (nb--)
	{
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
	}
}