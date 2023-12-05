/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 00:01:26 by pboonpro          #+#    #+#             */
/*   Updated: 2023/06/14 02:02:09 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	char	*ptr;
	int		i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (lens1 + lens2) + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < lens1 + lens2)
	{
		if (i < lens1)
			ptr[i] = s1[i];
		else if (i >= lens1 && i < lens1 + lens2)
			ptr[i] = s2[i - lens1];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
