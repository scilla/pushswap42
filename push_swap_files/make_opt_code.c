#include "../push_swap.h"

void	loop_move(int n, void (*f)(t_stack *, t_stack *),
				  t_stack *s_a, t_stack *s_b)
{
	while (n--)
		f(s_a, s_b);
}

void	make_opt_code0(t_moves *to_do, t_stack *stk_a, t_stack *stk_b)
{
	if (to_do->moves_a > to_do->moves_b)
	{
		loop_move(to_do->moves_b, &rr, stk_a, stk_b);
		loop_move(to_do->moves_a - to_do->moves_b, &rotate, stk_a, stk_a);
	}
	else
	{
		loop_move(to_do->moves_a, &rr, stk_a, stk_b);
		loop_move(to_do->moves_b - to_do->moves_a, &rotate, stk_b, stk_b);
	}
}

void	make_opt_code3(t_moves *to_do, t_stack *stk_a, t_stack *stk_b)
{
	if (to_do->moves_a > to_do->moves_b)
	{
		loop_move(to_do->moves_b, &rrr, stk_a, stk_b);
		loop_move(to_do->moves_a - to_do->moves_b,
			&inv_rotate, stk_a, stk_a);
	}
	else
	{
		loop_move(to_do->moves_a, &rrr, stk_a, stk_b);
		loop_move(to_do->moves_b - to_do->moves_a,
			&inv_rotate, stk_b, stk_b);
	}
}
