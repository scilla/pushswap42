/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:25:55 by scilla            #+#    #+#             */
/*   Updated: 2021/05/25 15:25:56 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	opt_code0(t_moves *to_do)
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

void	print_moves2(t_moves *to_do)
{
	if (to_do->opt_code == 0)
		opt_code0(to_do);
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

void	loop_print(char *cmd, int nb)
{
	while (nb--)
	{
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
	}
}
