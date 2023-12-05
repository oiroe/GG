/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:39:54 by pboonpro          #+#    #+#             */
/*   Updated: 2023/11/20 17:39:54 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genetic.h"

void	push(t_arr *arr, int num)
{
	if (arr->top >= arr->size - 1 || !arr)
		return ;
	arr->top++;
	arr->stack[arr->top] = num;
}

t_arr	*stack_init(unsigned int n)
{
	t_arr	*arr;

	arr = malloc(sizeof(t_arr) * 1);
	if (!arr)
		errorhand("Error");
	arr->stack = malloc(sizeof(int) * n);
	if (!arr->stack)
	{
		free(arr);
		errorhand("Error");
	}
	arr->size = n;
	arr->top = -1;
	return (arr);
}

char	*join_input(int ac, char **av)
{
	int		i;
	char	*join;
	char	*before;
	char	*del;

	i = 2;
	join = malloc(sizeof(char *) * 1);
	join[0] = '\0';
	while (i < ac)
	{
		before = ft_strjoin(" ", av[i]);
		del = join;
		join = ft_strjoin(join, before);
		free(before);
		free(del);
		i++;
	}
	return (join);
}

t_arr	*init_stack_a(int ac, char **av)
{
	int		i;
	int		count;
	char	**temp;
	char	*join;
	t_arr	*new;

	join = join_input(ac, av);
	count = countstr(join, ' ');
	temp = ft_split(join, ' ');
	free(join);
	new = stack_init(count);
	i = 0;
	while (temp[i])
	{
		push(new, ft_atoi(temp[i]));
		i++;
	}
	my_free(temp);
	return (new);
}
