/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:56:25 by pboonpro          #+#    #+#             */
/*   Updated: 2022/09/26 00:50:55 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countlen(int n)
{
	int				i;
	unsigned int	nb;

	i = 0;
	if (n < 0)
	{
		nb = n * (-1);
		i++;
	}
	else if (n == 0)
		return (1);
	else
		nb = n;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				i;
	int				last;
	unsigned int	nb;

	i = countlen(n);
	last = i;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == 0)
		return (0);
	if (n < 0)
		nb = n * (-1);
	else
		nb = n;
	i -= 1;
	while (i >= 0)
	{
		ptr[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		ptr[0] = '-';
	ptr[last] = '\0';
	return (ptr);
}
