#include "../push_swap.h"

void	loop_move(int n, void (*f)(t_stack *, t_stack *),
				t_stack *s_a, t_stack *s_b)
{
	while (n--)
		f(s_a, s_b);
}

void	make_opt_code0_(t_moves *to_do, t_stack *stk_a, t_stack stk_b)
{
	if (to_do->moves_a > to_do->moves_b)
	{
		loop_move(to_do->moves_b, &rr, stk_a, stk_b);
		loop_move(to_do->moves_a - to_do->moves_b, &rotate, stk_a, stk_a);
		//count = to_do->moves_a;
	}
	else
	{
		loop_move(to_do->moves_a, &rr, stk_a, stk_b);
		loop_move(to_do->moves_b - to_do->moves_a, &rotate, stk_b, stk_b);
		//count = to_do->moves_b;
	}
}

void	make_opt_code3_(t_moves *to_do, t_stack *stk_a, t_stack stk_b)
{
	if (to_do->moves_a > to_do->moves_b)
	{
		loop_move(to_do->moves_b, &rrr, stk_a, stk_b);
		loop_move(to_do->moves_a - to_do->moves_b,
			&inv_rotate, stk_a, stk_a);
		//count = to_do->moves_a;
	}
	else
	{
		loop_move(to_do->moves_a, &rrr, stk_a, stk_b);
		loop_move(to_do->moves_b - to_do->moves_a,
			&inv_rotate, stk_b, stk_b);
		//count = to_do->moves_b;
	}
}

int	make_moves(t_moves *to_do, t_stack *stk_a, t_stack *stk_b)
{
	int	count;

	if (to_do->opt_code == 0)
		make_opt_code0_(to_so, stk_a, stk_b);
	if (to_do->opt_code == 3)
		make_opt_code3_(to_do, stk_a, stk_b);
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

int	main(int argc, char **argv)
{
	t_stack	*arrA;
	t_stack	*arrB;
	t_stack	*lis;
	t_stack	*dup;
	t_stack	*dup_lis;
	t_moves	*to_do;
	int		count;
	int		spot;

	count = 0;
	arrA = parser(argc, argv);
	arrB = malloc(sizeof(t_stack));
	lis = malloc(sizeof(t_stack));
	arrB->data = malloc(0);
	arrB->len = 0;
	lis->data = malloc(0);
	lis->len = 0;
	ft_lis(arrA, &lis);
	dup_lis = malloc(sizeof(t_stack));
	dup_lis->data = malloc(0);
	dup_lis->len = 0;
	while (arrA->len > lis->len)
	{
		dup = stack_dup(arrA->data, arrA->len);
		swap(dup, dup);
		ft_lis(dup, &dup_lis);
		free(dup->data);
		free(dup);
		if (dup_lis->len > lis->len)
		{
			swap(arrA, arrA);
			ft_lis(arrA, &lis);
			write(1, "sa\n", 3);
			count++;
			continue ;
		}
		to_do = predict_moves(arrA, arrB, lis);
		count += make_moves(to_do, arrA, arrB);
		print_moves(to_do);
		free(to_do);
		push(arrA, arrB);
		write(1, "pb\n", 3);
		count++;
	}
	while (arrB->len)
	{
		spot = find_inv_spot(arrA, arrB->data[0]);
		if (spot < arrA->len / 2.0)
		{
			loop_move(spot, &rotate, arrA, arrA);
			print_moves(&(t_moves){spot, 0, 0, 1});
			count += spot;
		}
		else
		{
			loop_move(arrA->len - spot, &inv_rotate, arrA, arrA);
			print_moves(&(t_moves){arrA->len - spot, 0, 0, 2});
			count += arrA->len - spot;
		}
		push(arrB, arrA);
		write(1, "pa\n", 3);
		count++;
	}
	spot = min_in_arr(*arrA);
	if (spot < arrA->len / 2.0)
	{
		loop_move(spot, &rotate, arrA, arrA);
		print_moves(&(t_moves){spot, 0, 0, 1});
		count += spot;
	}
	else
	{
		loop_move(arrA->len - spot, &inv_rotate, arrA, arrA);
		print_moves(&(t_moves){arrA->len - spot, 0, 0, 2});
		count += arrA->len - spot;
	}
	free(arrB->data);
	free(arrB);
	free(dup_lis->data);
	free(dup_lis);
	free(arrA->data);
	free(arrA);
	free(lis->data);
	free(lis);
	return (1);
}
