/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meaw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:37:07 by pboonpro          #+#    #+#             */
/*   Updated: 2023/11/18 23:37:07 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genetic.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + (time.tv_usec));
}

int	check_input_c(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		av_check(av[i]);
		i++;
	}
}

void generateSecretCode(int *secret_code, int size)
{
	int	i;

	srand((unsigned int)get_time());
	i = 0;
	while (i < size)
	{
		secret_code[i] = rand() % COL;
		i++;
	}
}

t_arr	*generate_sol(int per)
{
	t_arr	*new;

	new = stack_init(per);
	generateSecretCode(new->stack, new->size);
	return (new);
}

int	main(void)
{
	int		colour;
	t_arr	*sol;
	int		*code;

	sol = generate_sol(PER);
	return (0);
}
