/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:03:58 by pboonpro          #+#    #+#             */
/*   Updated: 2022/10/01 23:04:47 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	led;
	size_t	les;
	size_t	j;

	les = ft_strlen(src);
	if (!dst && size == 0)
		return (ft_strlen(src));
	led = ft_strlen(dst);
	if (size == 0)
		return (les);
	if (size < led)
		return (size + les);
	j = 0;
	while (src[j] && led + 1 < size)
	{
		dst[led] = src[j];
		led++;
		j++;
	}
	dst[led] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}
