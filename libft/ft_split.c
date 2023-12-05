/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:29:20 by pboonpro          #+#    #+#             */
/*   Updated: 2022/09/29 00:04:54 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countstr(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	wordlen(const char *s, char c, int index)
{
	int	size;

	size = 0;
	while (s[index] && s[index] != c)
	{
		index++;
		size++;
	}
	return (size);
}

void	free_err(char **ptr, int i)
{
	while (i > 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	ptr = malloc(sizeof(char *) * (countstr(s, c) + 1));
	if (!s || !ptr)
		return (0);
	i = 0;
	j = 0;
	while (i < countstr(s, c))
	{
		while (s[j] == c)
			j++;
		ptr[i] = ft_substr(s, j, wordlen(s, c, j));
		if (!ptr[i])
		{
			free_err(ptr, i);
			return (0);
		}
		j += wordlen(s, c, j);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
