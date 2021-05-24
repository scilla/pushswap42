#include "../push_swap.h"

int	check_integer(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '-' || tmp[i] == '+')
			i++;
		if (!ft_isdigit(tmp[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_double_int(int *stack_a, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (stack_a[j] == stack_a[i])
			{
				if (i != j)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	find_len(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

int	*check_single_arg(char **av, int *len)
{
	char	**tmp;
	int		*stack_a;

	tmp = ft_split(av[1], ' ');
	*len = find_len(tmp);
	stack_a = malloc(sizeof(int) * (*len));
	*len = 0;
	while (tmp[*len])
	{
		if (check_integer(tmp[*len]))
		{
			stack_a[*len] = ft_atoi(tmp[*len]);
			(*len)++;
		}
		else
		{
			free_matrix(tmp);
			ft_error(stack_a);
		}
	}
	free_matrix(tmp);
	if (check_double_int(stack_a, *len))
		ft_error(stack_a);
	return (stack_a);
}

int	*check_more_args(int ac, char **av, int *len)
{
	int	*stack_a;
	int	i;

	stack_a = (int *)malloc(sizeof(int) * (ac - 1));
	i = 1;
	*len = ac - 1;
	while (i < ac)
	{
		if (check_integer(av[i]))
		{
			stack_a[i - 1] = ft_atoi(av[i]);
			i++;
		}
		else
			ft_error(stack_a);
	}
	if (check_double_int(stack_a, ac - 1))
		ft_error(stack_a);
	return (stack_a);
}
