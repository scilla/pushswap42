#include "../push_swap.h"

void	print_moves2(t_moves *to_do)
{
	if (to_do->opt_code == 0)
	{
		if (to_do->moves_a > to_do->moves_b)
		{
			loop_print("rr", to_do->moves_b);
			loop_print("ra", to_do->moves_a - to_do->moves_b);
		}
		else
		{
			loop_print("rr", to_do->moves_a);
			loop_print("rb", to_do->moves_b - to_do->moves_a);
		}
	}
	else if (to_do->opt_code == 3)
	{
		if (to_do->moves_a > to_do->moves_b)
		{
			loop_print("rrr", to_do->moves_b);
			loop_print("rra", to_do->moves_a - to_do->moves_b);
		}
		else
		{
			loop_print("rrr", to_do->moves_a);
			loop_print("rrb", to_do->moves_b - to_do->moves_a);
		}
	}
}

void	print_moves(t_moves *to_do)
{
	if (to_do->opt_code == 1)
	{
		loop_print("ra", to_do->moves_a);
		loop_print("rrb", to_do->moves_b);
	}
	else if (to_do->opt_code == 2)
	{
		loop_print("rra", to_do->moves_a);
		loop_print("rb", to_do->moves_b);
	}
	else
		print_moves2(to_do);
}
