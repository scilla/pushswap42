#include "../push_swap.h"

int	make_moves(t_moves *to_do, t_stack *stk_a, t_stack *stk_b)
{
	int	count;

	if (to_do->opt_code == 0)
		make_opt_code0(to_do, stk_a, stk_b);
	if (to_do->opt_code == 3)
		make_opt_code3(to_do, stk_a, stk_b);
	if (to_do->opt_code == 1)
	{
		loop_move(to_do->moves_a, &rotate, stk_a, stk_a);
		loop_move(to_do->moves_b, &inv_rotate, stk_b, stk_b);
		count = to_do->moves_a + to_do->moves_b;
	}
	if (to_do->opt_code == 2)
	{
		loop_move(to_do->moves_b, &rotate, stk_b, stk_b);
		loop_move(to_do->moves_a, &inv_rotate, stk_a, stk_a);
		count = to_do->moves_a + to_do->moves_b;
	}
	return (count);
}

void	init_stack(t_stack **stack)
{
	*stack = malloc(sizeof(t_stack));
	(*stack)->data = malloc(0);
	(*stack)->len = 0;
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_moves	*to_do;
	t_data	*var;

	var = malloc(sizeof(t_data));
	stack_a = parser(argc, argv);
	init_stack(&stack_b);
	init_stack(&var->lis);
	ft_lis(stack_a, &((*var).lis));
	init_stack(&var->dup_lis);
	while (stack_a->len > var->lis->len)
	{
		var->dup = stack_dup(stack_a->data, stack_a->len);
		swap(var->dup, var->dup);
		ft_lis(var->dup, &var->dup_lis);
		free_t_stack(var->dup);
		if (var->dup_lis->len > var->lis->len)
		{
			swap(stack_a, stack_a);
			ft_lis(stack_a, &var->lis);
			write(1, "sa\n", 3);
			continue ;
		}
		to_do = predict_moves(stack_a, stack_b, var->lis);
		make_moves(to_do, stack_a, stack_b);
		print_moves(to_do);
		free(to_do);
		push(stack_a, stack_b);
		write(1, "pb\n", 3);
	}
	while (stack_b->len)
	{
		var->spot = find_inv_spot(stack_a, stack_b->data[0]);
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
		push(stack_b, stack_a);
		write(1, "pa\n", 3);
	}
	var->spot = min_in_arr(*stack_a);
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
	free_t_stack(stack_b);
	free_t_stack(var->dup_lis);
	free_t_stack(stack_a);
	free_t_stack(var->lis);
	return (1);
}
