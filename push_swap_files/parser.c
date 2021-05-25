/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:26:02 by scilla            #+#    #+#             */
/*   Updated: 2021/05/25 15:26:02 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	parse_multi_args(int ac, char **av, t_stack *stack_a)
{
	int	i;

	stack_a->data = (int *)malloc(sizeof(int) * (ac - 1));
	i = 1;
	stack_a->len = ac - 1;
	while (i < ac)
	{
		if (check_integer(av[i]))
		{
			stack_a->data[i - 1] = ft_atoi(av[i]);
			i++;
		}
		else
			ft_error(stack_a->data);
	}
	if (check_double_int(stack_a->data, stack_a->len))
		ft_error(stack_a->data);
}

t_stack	*parser(int ac, char **av)
{
	t_stack	*stack_a;

	stack_a = malloc(sizeof(t_stack));
	if (ac <= 2)
	{
		if (ac == 2)
			stack_a->data = check_single_arg(av, &stack_a->len);
		else
			exit(0);
	}
	else
		parse_multi_args(ac, av, stack_a);
	return (stack_a);
}
