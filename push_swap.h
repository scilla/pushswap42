/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:54:48 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/05/24 18:38:10 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_stack
{
	int			*data;
	int			len;
}				t_stack;

typedef struct s_moves
{
	int			moves_a;
	int			moves_b;
	int			abs_moves;
	int			opt_code;
}				t_moves;

typedef struct s_index
{
	int			index_a;
	int			index_b;
	int			len_a;
	int			len_b;
}				t_index;

typedef struct s_data
{
	t_stack		*dup;
	t_stack		*lis;
	t_stack		*dup_lis;
	int			spot;
}				t_data;

/*
**	CHECKER
*/

void	start_checker(int *stack_a, int size);
void	receive_commands(t_list **stack_a, t_list **stack_b);
void	give_result(t_list *stack_a, t_list *stack_b);
void	swap_first_two_elements(t_list **stack);
void	push_stack(t_list **stack_a, t_list **stack_b);
void	rotate_stack(t_list **stack);
void	reverse_rotate(t_list **stack);
void	free_stack(t_list **stack);
void	adjust_index(t_list **stack);
void	free_matrix(char **matrix);
void	ft_error(int *stack_a);
int		*check_more_args(int ac, char **av, int *len);

/*
**	main.c
*/

int		min_stack(t_stack *stack);
int		max_stack(t_stack **stack, int len);
t_stack	*stack_dup(int *data, int len);

/*
**	lis.c
*/

void	ft_lis(t_stack *stk_s, t_stack **stk_d);
void	print_stack(t_stack *src);
void	free_t_stack(t_stack *stack);

/*
**	moves.c
*/

void	swap(t_stack *stk, t_stack *fuffa);
void	rotate(t_stack *stk, t_stack *fuffa);
void	inv_rotate(t_stack *stk, t_stack *fuffa);
void	rr(t_stack *stk_a, t_stack *stk_b);
void	rrr(t_stack *stk_a, t_stack *stk_b);
void	push(t_stack *stk_s, t_stack *stk_d);

/*
** PUSH SWAP
*/

t_stack	*parser(int ac, char **av);
int		find_spot(t_stack *stk_b, int value);
int		find_inv_spot(t_stack *stk_b, int value);
t_moves	*predict_moves(t_stack *stk_a, t_stack *stk_b, t_stack *lis);
int		min_in_arr(t_stack stack);
int		max_in_arr(t_stack stack);
int		check_in_lis(int value, t_stack *lis);
void	make_opt_code0(t_moves *to_do, t_stack *stk_a, t_stack *stk_b);
void	make_opt_code3(t_moves *to_do, t_stack *stk_a, t_stack *stk_b);
void	check_stack(t_stack *stack, char *dir);
void	print_moves(t_moves *to_do);
void	loop_print(char *cmd, int nb);
void	final_rotate(t_data *var, t_stack *stack_a);
void	loop_move(int n, void (*f)(t_stack *, t_stack *),
			t_stack *s_a, t_stack *s_b);

/*
** parser.c
*/

int		*check_single_arg(char **av, int *len);
int		check_double_int(int *stack_a, int size);
int		check_integer(char *tmp);

#endif