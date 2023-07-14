/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_big_atol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:09 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long	ft_big_atol(const char *str)
{
	long	result;
	int		negative;
	int		a;

	negative = 1;
	a = ft_atoi_check(str, &negative);
	result = ft_add_str_to_int(str, &a);
	if (result > LONG_MAX && negative == -1)
		return (0);
	else if (result > LONG_MAX && negative == 1)
		return (-1);
	return (result * negative);
}
