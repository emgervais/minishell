/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:10:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:10:57 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_putnbr(int n)
{
	long int	a;
	int			count;

	a = n;
	count = 0;
	if (a < 0)
	{
		count += ft_int_putchar('-');
		a = -a;
	}
	if (a > 9)
	{
		count += ft_int_putnbr(a / 10);
		a %= 10;
	}
	count += ft_int_putchar(a + '0');
	return (count);
}
