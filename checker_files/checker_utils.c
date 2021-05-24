#include "../push_swap.h"

void	free_stack(t_list **stack)
{
	t_list	*tmp;

	tmp = *stack;
	while (*stack)
	{
		free(tmp->next);
		tmp->next = NULL;
		*stack = (*stack)->next;
	}
}

void	adjust_index(t_list **stack)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *stack;
	if (*stack)
	{
		while (tmp)
		{
			tmp->index = i;
			i++;
			tmp = tmp->next;
		}
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	matrix = NULL;
}

void	ft_error(int *stack_a)
{
	write(1, "Error\n", 6);
	free(stack_a);
	stack_a = NULL;
	exit(0);
}