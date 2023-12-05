/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:30:53 by pboonpro          #+#    #+#             */
/*   Updated: 2023/11/20 17:30:53 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genetic.h"

void	my_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	errorhand(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	check_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '\0')
		return (0);
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

void	do_check(char **temp, int i, char **trash)
{
	long	check;

	if (temp[0] == (void *)0)
		errorhand("Error");
	while (temp[i])
	{
		check = ft_atol(temp[i]);
		if (!check_isnum(temp[i]))
		{
			my_free(trash);
			errorhand("Error");
		}
		if (check < -2147483648 || check > 2147483647)
		{
			my_free(trash);
			errorhand("Error");
		}
		i++;
	}
}

void	av_check(char *av)
{
	size_t	i;
	int		count;
	char	*temp;

	temp = av;
	count = 0;
	i = 0;
	while (i < strlen(temp))
	{
		if (ft_isdigit(temp[i]))
			count++;
		i++;
	}
	if (count == 0)
		errorhand("Error");
}

void	check_input(int ac, char **av)
{
	int		i;
	char	**temp;
	char	*join;

	i = 1;
	while (i < ac)
	{
		av_check(av[i]);
		i++;
	}
	join = join_input(ac, av);
	temp = ft_split(join, ' ');
	free(join);
	do_check(temp, 0, temp);
	my_free(temp);
}
