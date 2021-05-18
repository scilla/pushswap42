/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scilla <scilla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:02:00 by scilla            #+#    #+#             */
/*   Updated: 2021/05/18 19:17:30 by scilla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void	rotate(int *stack, int len)
{
	int	tmp;
	int	i;

	if (!len)
		return ;
	i = 0;
	tmp = stack[0];
	while (i < len - 1)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	stack[i] = tmp;
}

void	inv_rotate(int *stack, int len)
{
	int	tmp;
	int	i;

	if (!len)
		return ;
	i = len - 1;
	tmp = stack[len - 1];
	while (i > 0)
	{
		stack[i] = stack[i - 1];
		i--;
	}
	stack[0] = tmp;
}

void	rr(int **stackA, int **stackB, int *lenA, int *lenB)
{
	rotate(*stackA, *lenA);
	rotate(*stackB, *lenB);
}

void	rrr(int **stackA, int **stackB, int *lenA, int *lenB)
{
	inv_rotate(*stackA, *lenA);
	inv_rotate(*stackB, *lenB);
}

void	push(int **src, int **dst, int *len_src, int *len_dst)
{
	int	*new_src;
	int	*new_dst;
	int	i;
	
	if (!len_src)
		return ;
	new_src = malloc(sizeof(int) * (*len_src - 1));
	new_dst = malloc(sizeof(int) * (*len_dst + 1));
	new_dst[0] = (*src)[0];
	i = *len_src;
	while (i > 0)
	{
		new_src[i - 2] = (*src)[i - 1];
		i--;
	}
	i = *len_dst;
	while (i > 0)
	{
		new_dst[i] = (*dst)[i - 1];
		i--;
	}
	free(*src);
	free(*dst);
	*src = new_src;
	*dst = new_dst;
	(*len_dst)++;
	(*len_src)--;
}

int	min_in_stack(int *stack, int len)
{
	int res;
	int	i;
	
	res = stack[0];
	i = 0;
	while (i < len)
	{
		if (stack[i] < res)
			res = stack[i];
		i++;
	}
	return (res);
}

int	max_in_stack(int *stack, int len)
{
	int res;
	int	i;
	
	res = stack[0];
	i = 0;
	while (i < len)
	{
		if (stack[i] > res)
			res = stack[i];
		i++;
	}
	return (res);
}

int	*stack_dup(int *src, int len)
{
	int	*dst;
	
	dst = malloc(sizeof(int) * len);
	while (len > 0)
	{
		len--;
		dst[len] = src[len];
	}
	return (dst);
}
void	print_stack(int *src, int len)
{
	int i;
	
	i = 0;
	while (i < len)
	{
		printf("%d\n", src[i]);
		i++;
	}
}

void	LIS(int *src, int **dst, int src_len, int *dst_len)
{
	int *dup;
	int **reg;
	int	*reg_lens;
	int	i;
	int	j;

	dup = stack_dup(src, src_len);
	while (min_in_stack(dup, src_len) != dup[0])
	{
		rotate(dup, src_len);
	}
	reg = malloc(sizeof(int *) * src_len);
	reg_lens = malloc(sizeof(int) * src_len);
	i = 0;
	while (i < src_len)
	{
		reg[i] = malloc(sizeof(int) * src_len);
		reg_lens[i] = 0;
		i++;
	}
	reg[0][0] = dup[0];
	reg_lens[0]++;
	i = 1;
	while (i < src_len)
	{
		j = 0;
		while (j < i)
		{
			if (dup[j] < dup[i] && reg_lens[i] < reg_lens[j])
			{
				free(reg[i]);
				reg[i] = stack_dup(reg[j], reg_lens[j]);
				reg_lens[i] = reg_lens[j];
			}
			j++;
		}
		reg[i][reg_lens[i]] = dup[i];
		reg_lens[i]++;
		i++;
	}
	i = max_in_stack(reg_lens, src_len);
	j = 0;
	while (i != reg_lens[j])
		j++;
	*dst = stack_dup(reg[j], reg_lens[j]);
	*dst_len = reg_lens[j];
	i = 0;
	while (i < src_len)
	{
		free(reg[i]);
		i++;
	}
	free(reg);
	free(reg_lens);
}

void	sort(int **stackA, int lenA)
{
	t_stack	*A;
	t_stack *B;
	t_stack *lis;
	
	B = malloc(sizeof(t_stack));
	A = malloc(sizeof(t_stack));
	lis = malloc(sizeof(t_stack));
	A->data = *stackA;
	A->len = lenA;
	B->data = malloc(0);
	B->len = 0;
	LIS(A->data, &lis->data, A->len, &lis->len);
	while (A->len > lis->len)
	{
		push(&A->data, &B->data, &A);
	}
	
}

int main(int argc, char **argv)
{
	int	*arrA;
	int	*arrB;
	int	**lis;
	int	lis_len;
	
	lis = malloc(sizeof(int*));
	arrA = malloc(sizeof(int) * 6);
	arrB = malloc(0);
	
	arrA[0] = atoi(argv[1]);
	arrA[1] = atoi(argv[2]);
	arrA[2] = atoi(argv[3]);
	arrA[3] = atoi(argv[4]);

	sort(&arrA, 4);
	return 1;

	LIS(arrA, lis, 4, &lis_len);
	
	printf("LIS len %d\n", lis_len);
	for (int i = 0; i < lis_len; i++)
	{
		printf("LIS %d\n", (*lis)[i]);
	}
	return (1);
	

	int arr_lenA = 4;
	int arr_lenB = 0;
	
	for (int i = 0; i < arr_lenA; i++)
	{
		printf("A %d\n", arrA[i]);
	}
	for (int i = 0; i < arr_lenB; i++)
	{
		printf("B %d\n", arrB[i]);
	}
	
	printf("PUSHAAAAaa\n");
	push(&arrA, &arrB, &arr_lenA, &arr_lenB);
	push(&arrA, &arrB, &arr_lenA, &arr_lenB);

	for (int i = 0; i < arr_lenA; i++)
	{
		printf("A %d\n", arrA[i]);
	}for (int i = 0; i < arr_lenB; i++)
	{
		printf("B %d\n", arrB[i]);
	}
	return 1;
}