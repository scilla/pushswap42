#include "../push_swap.h"

void	swap_first_two_elements(t_list **stack)
{
	int	first;
	int	second;

	if (*stack && (*stack)->next)
	{
		first = (*stack)->nb;
		second = (*stack)->next->nb;
		(*stack)->nb = second;
		(*stack)->next->nb = first;
		adjust_index(stack);
	}
}

void	push_stack(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	if (*stack_b)
	{
		tmp = (*stack_b)->next;
		ft_lstadd_front(stack_a, *stack_b);
		*stack_b = tmp;
		if (tmp)
			(*stack_b)->previous = NULL;
		adjust_index(stack_a);
		adjust_index(stack_b);
	}
}

void	rotate_stack(t_list **stack)
{
	t_list	*first;
	t_list	*last;

	if (*stack)
	{
		first = *stack;
		last = *stack;
		*stack = (*stack)->next;
		while (last->next)
			last = last->next;
		last->next = first;
		first->previous = last;
		first->next = NULL;
		adjust_index(stack);
	}
}

void	reverse_rotate(t_list **stack)
{
	t_list	*tmp_second;
	t_list	*tmp_new_first;

	if (*stack && (*stack)->next)
	{
		tmp_second = *stack;
		tmp_new_first = *stack;
		while (tmp_new_first->next)
			tmp_new_first = tmp_new_first->next;
		tmp_new_first->next = tmp_second;
		tmp_new_first->previous->next = NULL;
		tmp_new_first->previous = NULL;
		tmp_second->previous = tmp_new_first;
		*stack = tmp_new_first;
		adjust_index(stack);
	}
}
