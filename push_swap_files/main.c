#include "../push_swap.h"

void free_matrix(char **matrix)
{
    int i;

    i = 0;
    while(matrix[i])
        free(matrix[i++]);
    free(matrix);
    matrix = NULL;
}

void ft_error(int *stack_a)
{
    write(1, "Error\n", 6);
    free(stack_a);
    stack_a = NULL;
    exit(0);
}

int check_integer(char *tmp)
{
    int i;

    i = 0;
    while(tmp[i])
    {
        if(tmp[i] == '-' || tmp[i] == '+')
            i++;
        if(!ft_isdigit(tmp[i]))
            return(0);
        i++;
    }
    return(1);
}

int check_double_int(int *stack_a)
{
    int i;
	int j;

    i = 0;
    while(stack_a[i])
    {
        j = 0;
        while(stack_a[j])
        {
			if(stack_a[j] == stack_a[i])
			{
				if(i != j)
				    return(1);
			}
            j++;
        }
        i++;
    }
    return(0);
}

void check_single_arg(int *stack_a, int ac, char **av)
{
    int i;
    int k;
    char **tmp;

    tmp = ft_calloc(sizeof(char *), (ac - 1));
    tmp = ft_split(av[1], ' ');
    i = 1;
    k = 0;
    while(tmp[k])
    {
        if(check_integer(tmp[k]))
        {
            stack_a[k] = ft_atoi(tmp[k]);
            k++;
        }
        else
        {
            free_matrix(tmp);
            ft_error(stack_a);
        }
    }
    free_matrix(tmp);
    if(check_double_int(stack_a))
        ft_error(stack_a);
}


int main(int ac, char**av)
{
    int *stack_a;
    int *stack_b;
    int i;
    int k;

    if(ac <= 2)
    {
        if(ac == 2)
		{
			stack_a = ft_calloc(sizeof(int), ac - 1);
            check_single_arg(stack_a, ac, av);
		}
        else
            exit(0);
    }
    else
    {
        stack_a = malloc(sizeof(int) * (ac - 1));
        i = 1;
        k = 0;
        while(i < ac && check_integer(av[i]))
        {
            if(check_integer(av[i]))
            {
                stack_a[k] = ft_atoi(av[i]);
                i++;
                k++;
            }
            else
                ft_error(stack_a);
        }
        if(check_double_int(stack_a))
            ft_error(stack_a);
    }
    printf("OK\n");
}
