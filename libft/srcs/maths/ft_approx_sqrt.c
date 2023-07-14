/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_approx_sqrt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:07:48 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:18:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_approx_sqrt(int nb)
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
	if (ft_abs((end * end) - nb) < ft_abs((end + 1) * (end + 1) - nb))
		return ((int)end);
	else
		return ((int)end + 1);
}
