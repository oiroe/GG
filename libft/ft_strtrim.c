/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:06:54 by pboonpro          #+#    #+#             */
/*   Updated: 2022/09/24 20:10:13 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	size_t			lens1;
	char			*ptr;

	if (s1 == 0 || set == 0)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	lens1 = ft_strlen(s1) - i;
	while (lens1 && ft_strchr(set, s1[lens1 + i]))
		lens1--;
	ptr = ft_substr(&s1[i], 0, lens1 + 1);
	return (ptr);
}
