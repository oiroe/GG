/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:28:40 by pboonpro          #+#    #+#             */
/*   Updated: 2023/01/12 23:28:40 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include "libft.h"

char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen_new(const char *s, int mode);
char	*ft_strjoin_new(char *old, char *to_join);
char	*trimming_stored(char *stored_next);
char	*trimming_return(char *stored_next);
char	*reading(int fd, char *to_return);
char	*get_next_line(int fd);
char	*ft_strdup_new(char *s1, int mode);

#endif
