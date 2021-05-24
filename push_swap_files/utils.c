#include "../push_swap.h"

/*
**	OP_CODE:
**	0 A+ B+   1 A+ B-   2 A- B+   3 A- B-
*/

void	count_moves2(t_index *dio, t_moves *curr, int k)
{
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = dio->len_a - dio->index_a;
		curr->moves_b = dio->len_b - dio->index_b;
		curr->opt_code = 3;
	}
	k = dio->index_a + dio->len_b - dio->index_b;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = dio->index_a;
		curr->moves_b = dio->len_b - dio->index_b;
		curr->opt_code = 1;
	}
	k = dio->len_a - dio->index_a + dio->index_b;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = dio->len_a - dio->index_a;
		curr->moves_b = dio->index_b;
		curr->opt_code = 2;
	}
}

t_moves	*count_moves(t_index *dio)
{
	t_moves	*curr;
	int		k;

	curr = malloc(sizeof(t_moves));
	curr->abs_moves = 9999;
	k = dio->index_b;
	if (dio->index_a > dio->index_b)
		k = dio->index_a;
	if (k < curr->abs_moves)
	{
		curr->abs_moves = k;
		curr->moves_a = dio->index_a;
		curr->moves_b = dio->index_b;
		curr->opt_code = 0;
	}
	k = dio->len_b - dio->index_b;
	if (dio->len_a - dio->index_a > dio->len_b - dio->index_b)
		k = dio->len_a - dio->index_a;
	count_moves2(dio, curr, k);
	return (curr);
}

t_index	*init_index(int index_a, int index_b, int len_a, int len_b)
{
	t_index	*dio;

	dio = malloc(sizeof(t_index));
	dio->index_a = index_a;
	dio->index_b = index_b;
	dio->len_a = len_a;
	dio->len_b = len_b;
	return (dio);
}

void	choose_best(t_moves **best, t_moves *curr)
{
	if (curr->abs_moves < (*best)->abs_moves)
	{
		free((*best));
		(*best) = curr;
	}
	else
		free(curr);
}

t_moves	*predict_moves(t_stack *stk_a, t_stack *stk_b, t_stack *lis)
{
	int				i;
	int				index_b;
	t_moves			*best;
	t_moves			*curr;
	t_index			*dio;

	i = 0;
	best = malloc(sizeof(t_moves));
	best->abs_moves = 9999;
	while (i < stk_a->len)
	{
		if (check_in_lis(stk_a->data[i], lis))
		{
			i++;
			continue ;
		}
		index_b = find_spot(stk_b, stk_a->data[i]);
		dio = init_index(i, index_b, stk_a->len, stk_b->len);
		curr = count_moves(dio);
		choose_best(&best, curr);
		i++;
	}
	return (best);
}
