/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:07:57 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:15:25 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_find_next_prime(int nb)
{
	int	a;

	if (nb <= 2)
		return (2);
	a = nb;
	if (a % 2 == 0)
		a++;
	while (a)
	{
		if (ft_isprime(a))
			return (a);
		a += 2;
	}
	return (0);
}
