/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:49:39 by pboonpro          #+#    #+#             */
/*   Updated: 2022/10/01 04:30:52 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	if (*tofind == 0)
		return ((char *)str);
	if (len == 0)
		return (0);
	i = 0;
	while (str[i] != 0 && i < len)
	{
		j = 0;
		while (tofind[j] == str[i + j] && i + j < len
			&& str[i + j] && tofind[j])
		{
			j++;
			if (tofind[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}
