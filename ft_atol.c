/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:53:31 by pboonpro          #+#    #+#             */
/*   Updated: 2023/11/20 18:53:31 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genetic.h"

long	ft_atol(const char *str)
{
	long	sum;
	int		sign;
	int		i;

	sum = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + str[i] - '0';
		i++;
	}
	return (sum * sign);
}
