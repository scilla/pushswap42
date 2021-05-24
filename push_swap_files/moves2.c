#include "../push_swap.h"

void	swap(t_stack *stk, t_stack *fuffa)
{
	int	tmp;

	(void)fuffa;
	tmp = stk->data[0];
	stk->data[0] = stk->data[1];
	stk->data[1] = tmp;
}

void	rotate(t_stack *stk, t_stack *fuffa)
{
	int	tmp;
	int	i;

	(void)fuffa;
	if (!stk->len)
		return ;
	i = 0;
	tmp = stk->data[0];
	while (i < stk->len - 1)
	{
		stk->data[i] = stk->data[i + 1];
		i++;
	}
	stk->data[i] = tmp;
}

void	inv_rotate(t_stack *stk, t_stack *fuffa)
{
	int	tmp;
	int	i;

	(void)fuffa;
	if (!stk->len)
		return ;
	i = stk->len - 1;
	tmp = stk->data[stk->len - 1];
	while (i > 0)
	{
		stk->data[i] = stk->data[i - 1];
		i--;
	}
	stk->data[0] = tmp;
}
