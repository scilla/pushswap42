#include "../push_swap.h"

void free_stack(t_list **stack)
{
	t_list *tmp;
	
	tmp = *stack;
	
	while(*stack)
	{
		//*stack = (*stack)->next;
		free(tmp->next);
		tmp->next = NULL;
		*stack = (*stack)->next;
	}
}

void adjust_index(t_list **stack) // la chiamo ogni qualvolta modifico con i comandi la lista in modo da settare nuovamente bene l' indice
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = *stack;
	if(*stack)
	{
		while(tmp)
		{
			tmp->index = i;
			i++;
			tmp = tmp->next;
		}
	}
}

void swap_first_two_elements(t_list **stack)  //lo uso sia per il comando "sa" che "sb"
{
	int first;
	int second;
	
	if(*stack && (*stack)->next)
	{
		first = (*stack)->nb;
		second = (*stack)->next->nb;
		(*stack)->nb = second;
		(*stack)->next->nb = first;
		adjust_index(stack);
	}
}

void push_on_a(t_list **stack_a, t_list **stack_b) //prendo primo elemento di B e lo metto sul top della stack A comando "pa"
{
	t_list *tmp;
	
	if(*stack_b)
	{
		tmp = (*stack_b)->next;
		ft_lstadd_front(stack_a, *stack_b);
		*stack_b = tmp;
		if(tmp)
			(*stack_b)->previous = NULL;
		adjust_index(stack_a);
		adjust_index(stack_b);
	}
}


void push_on_b(t_list **stack_a, t_list **stack_b) //prendo primo elemento di A e lo metto sul top della stack B comando "pb"
{
	t_list *tmp;
	
	if(*stack_a)
	{
		tmp = (*stack_a)->next;
		ft_lstadd_front(stack_b, *stack_a);
		*stack_a = tmp;
		if(tmp)
			(*stack_a)->previous = NULL;
		adjust_index(stack_a);
		adjust_index(stack_b);
	}
}

// da fare ra, rb -> primo argomento diventa ultimo nella stack

void rotate_stack(t_list **stack)
{
	t_list *first;
	t_list *last;
	
	if(*stack)
	{
		first = *stack;
		last = *stack;
		*stack = (*stack)->next;
		while(last->next)
			last = last->next;
		last->next = first;
		first->previous = last;
		first->next = NULL;
		adjust_index(stack);
	}
}

// da fare rra e rrb -> il primo argomento diventa l-ultimo e l-ultimo diventa primo
void reverse_rotate(t_list **stack)
{
	t_list *tmp_second;
	t_list *tmp_new_first;

	if(*stack)
	{
		tmp_second = *stack; // prima posizione che diventa seconda
		tmp_new_first = *stack;
		while(tmp_new_first->next)
			tmp_new_first = tmp_new_first->next;
		tmp_new_first->next = tmp_second;
		tmp_new_first->previous->next = NULL;
		tmp_new_first->previous = NULL;
		tmp_second->previous = tmp_new_first;
		*stack = tmp_new_first;
		adjust_index(stack);
	}
}




