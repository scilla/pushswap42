/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:54:48 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/05/21 17:41:03 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct	s_stack
{
	int	*data;
	int	len;
}				t_stack;

typedef struct	s_moves
{
	int	moves_a;
	int	moves_b;
	int	abs_moves;
	int opt_code;
}				t_moves;

/*
**	CHECKER
*/
void	start_checker(int *stack_a, int size);
void	receive_commands(t_list **stack_a,t_list **stack_b);
void	give_result(t_list *stack_a, t_list *stack_b);
void	swap_first_two_elements(t_list **stack);
void	push_on_a(t_list **stack_a, t_list **stack_b);
void	push_on_b(t_list **stack_a, t_list **stack_b);
void	rotate_stack(t_list **stack);
void	reverse_rotate(t_list **stack);
void	free_stack(t_list **stack);

/*
** PUSH SWAP
*/

t_stack *parser(int ac, char **av);
int		find_spot(t_stack *stk_b, int value);
int		find_inv_spot(t_stack *stk_b, int value);
t_moves	*predict_moves(t_stack *stk_a, t_stack *stk_b, t_stack *lis);
int	min_in_arr(t_stack stack);
int	max_in_arr(t_stack stack);

# endif