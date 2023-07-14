/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:08:20 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:15:34 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_power(int nb, int power)
{
	int	result;

	result = 1;
	if ((nb == 0 && power != 0) || power < 0)
		return (0);
	if ((nb < 0 && power == 0) || (power == 0))
		return (1);
	else
	{
		while (power > 0)
		{
			result = result * nb;
			power--;
		}
	}
	return (result);
}
