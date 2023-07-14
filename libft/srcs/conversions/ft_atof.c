/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:16 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:01 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float	ft_atof(const char *str)
{
	int		result;
	float	decimal;
	int		negative;
	int		point;
	int		a;

	negative = 1;
	decimal = 0;
	point = 1;
	a = ft_atoi_check(str, &negative);
	result = ft_add_str_to_int(str, &a);
	if (str[a] == '.')
	{
		a++;
		point = a;
		decimal = ft_add_str_to_int(str, &a);
		point = a - point;
	}
	return ((result + (decimal / ft_power(10, point))) * negative);
}
