/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:01:34 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:25:58 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATHS_H
# define FT_MATHS_H

# include "libft.h"

/*/////////////////////////////////////////////////////////////////////////////
		MATHS FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

int		ft_approx_sqrt(int nb);
int		ft_sqrt(int nb);
int		ft_factorial(int nb);
int		ft_power(int nb, int power);
int		ft_get_highest(int nb1, int nb2);
int		ft_get_lowest(int nb1, int nb2);
int		ft_find_next_prime(int nb);
double	ft_percent(int start, int end, int current);
int		ft_abs(int n);

#endif //FT_MATHS_H