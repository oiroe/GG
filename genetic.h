/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genetic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:37:30 by pboonpro          #+#    #+#             */
/*   Updated: 2023/11/18 23:37:30 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENETIC_H
# define GENETIC_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include "libft/libft.h"

# ifndef PER
#  define PER 4
# endif

# ifndef COL
#  define COL 6
# endif

typedef struct s_arr
{
	int	*stack;
	int	size;
	int	top;
}			t_arr;

typedef struct s_pegs
{
	int	black;
	int	white;
}			t_pegs;

typedef struct s_gen
{
	t_pegs	*pegs;
	int		**data;
	int		size_data;
	int		size_gen;
}			t_gen;

t_arr	*stack_init(unsigned int n);
void	av_check(char *av);
t_arr	*stack_init(unsigned int n);
long	ft_atol(const char *str);
void	my_free(char **str);
void	errorhand(char *str);
char	*join_input(int ac, char **av);
int		countstr(char const *s, char c);

#endif
