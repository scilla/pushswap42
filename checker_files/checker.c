#include "../push_swap.h"

void	start_checker(int *stack_a, int size)
{
	int		i;
	t_list	*tmp_a;
	t_list	*real_a;
	t_list	*real_b;

	i = 0;
	real_a = 0;
	real_b = 0;
	while (i < size)
	{
		tmp_a = ft_lstnew(stack_a[i], i);
		ft_lstadd_back(&real_a, tmp_a);
		i++;
	}
	//free_stack(&tmp_a);
	receive_commands(&real_a, &real_b);
	give_result(real_a, real_b);
	if (real_a)
		free_stack(&real_a);
	if (real_b)
		free_stack(&real_b);
}
