/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:10:50 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:03 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_putnbr_fd(int n, int fd)
{
	long int	a;
	int			count;

	a = n;
	count = 0;
	if (a < 0)
	{
		count += ft_int_putchar_fd('-', fd);
		a = -a;
	}
	if (a > 9)
	{
		count += ft_int_putnbr_fd(a / 10, fd);
		a %= 10;
	}
	count += ft_int_putchar_fd(a + '0', fd);
	return (count);
}
