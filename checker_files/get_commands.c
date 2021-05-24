/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:48:27 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/05/24 15:25:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	activate_command_2(char *cmd, t_list **stack_a, t_list **stack_b)
{
	if (!ft_strcmp(cmd, "ss"))
	{
		swap_first_two_elements(stack_a);
		swap_first_two_elements(stack_b);
	}
	if (!ft_strcmp(cmd, "pa"))
		push_on_a(stack_a, stack_b);
	if (!ft_strcmp(cmd, "pb"))
		push_on_b(stack_a, stack_b);
	if (!ft_strcmp(cmd, "rr"))
	{
		rotate_stack(stack_a);
		rotate_stack(stack_b);
	}
}

void	activate_command_1(char *cmd, t_list **stack_a, t_list **stack_b)
{
	if (!ft_strcmp(cmd, "sa"))
		swap_first_two_elements(stack_a);
	if (!ft_strcmp(cmd, "sb"))
		swap_first_two_elements(stack_b);
	if (!ft_strcmp(cmd, "ra"))
		rotate_stack(stack_a);
	if (!ft_strcmp(cmd, "rb"))
		rotate_stack(stack_b);
	if (!ft_strcmp(cmd, "rra"))
		reverse_rotate(stack_a);
	if (!ft_strcmp(cmd, "rrb"))
		reverse_rotate(stack_b);
	if (!ft_strcmp(cmd, "rrr"))
	{
		reverse_rotate(stack_a);
		reverse_rotate(stack_b);
	}
}

void	give_result(t_list *stack_a, t_list *stack_b)
{
	t_list	*tmp_b;
	int		i;

	i = 1;
	tmp_b = stack_b;
	if (stack_a && !tmp_b)
	{
		while (stack_a->next)
		{
			if (stack_a->nb < stack_a->next->nb)
				stack_a = stack_a->next;
			else
			{
				write(1, "KO\n", 3);
				break ;
			}
		}
		if (stack_a->next == NULL)
			write(1, "OK\n", 3);
	}
	if (tmp_b != NULL)
		write(1, "KO\n", 3);
}

void	receive_commands(t_list **stack_a, t_list **stack_b)
{
	char	**cmd;

	cmd = malloc(sizeof(char *));
	while (get_next_line(0, cmd) > 0)
	{
		if (!ft_strcmp(*cmd, "ss") || !ft_strcmp(*cmd, "rr")
			|| !ft_strcmp(*cmd, "pa") || !ft_strcmp(*cmd, "pb"))
			activate_command_2(*cmd, stack_a, stack_b);
		else if (!ft_strcmp(*cmd, "sa") || !ft_strcmp(*cmd, "sb")
			|| !ft_strcmp(*cmd, "ra") || !ft_strcmp(*cmd, "rb")
			|| !ft_strcmp(*cmd, "rra") || !ft_strcmp(*cmd, "rrb")
			|| !ft_strcmp(*cmd, "rrr"))
			activate_command_1(*cmd, stack_a, stack_b);
		else
			write(1, "Command does not exist\n", 23);
	}
}
