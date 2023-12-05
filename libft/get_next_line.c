/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:28:24 by pboonpro          #+#    #+#             */
/*   Updated: 2023/01/12 23:28:24 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char	*ft_free(char *buffer, char *buff)
{
	char	*temp;

	temp = ft_strjoin(buffer, buff);
	free(buffer);
	return (temp);
}*/

char	*trimming_stored(char *stored_next)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stored_next[i] && stored_next[i] != '\n')
		i++;
	if (!stored_next[i])
	{
		free(stored_next);
		return (NULL);
	}
	str = ft_calloc((ft_strlen_new(stored_next, 0) - i + 1), sizeof(char));
	i += 1;
	j = 0;
	while (stored_next[i])
	{
		str[j] = stored_next[i];
		i++;
		j++;
	}
	free(stored_next);
	return (str);
}

/*char	*trimming_return(char *stored_next)
{
	int		i;
	char	*str;

	i = 0;
	if (!stored_next[i])
		return (0);
	while (stored_next[i] && stored_next[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stored_next[i] && stored_next[i] != '\n')
	{
		str[i] = stored_next[i];
		i++;
	}
	if (stored_next[i] && stored_next[i] == '\n')
		str[i] = '\n';
	return (str);
}*/

char	*trimming_return(char *str)
{
	char	*buff;

	if (!str[0])
		return (0);
	if (ft_strchr(str, '\n'))
		buff = ft_strdup_new(str, 1);
	else
		buff = ft_strdup_new(str, 0);
	return (buff);
}

char	*reading(int fd, char *to_return)
{
	char	*temp;
	int		byte_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (0);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(temp);
			return (0);
		}
		temp[byte_read] = '\0';
		to_return = ft_strjoin_new(to_return, temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (to_return);
}

char	*get_next_line(int fd)
{
	char		*to_return;
	static char	*stored_next;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored_next = reading(fd, stored_next);
	if (!stored_next)
		return (0);
	to_return = trimming_return(stored_next);
	stored_next = trimming_stored(stored_next);
	return (to_return);
}
