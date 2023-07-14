/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:09:28 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:19:44 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_sqrt(int nb)
{
	long	start;
	long	mid;
	long	end;

	start = 1;
	end = nb;
	if (nb == 0 || nb == 1)
		return (nb);
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid * mid == nb)
			return ((int)mid);
		if (mid * mid < nb)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return (0);
}
