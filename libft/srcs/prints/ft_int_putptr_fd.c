/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putptr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:11:00 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:07 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_int_putptr_base_fd(unsigned long long nbr, char *base, int fd)
{
	int					count;
	unsigned long long	hexptr;
	size_t				baselen;

	count = 0;
	hexptr = nbr;
	baselen = ft_strlen(base);
	if (hexptr >= baselen)
		count += ft_int_putptr_base_fd(hexptr / baselen, base, fd);
	count += ft_int_putchar_fd(base[hexptr % baselen], fd);
	return (count);
}

int	ft_int_putptr_fd(unsigned long long nbr, int fd)
{
	int	count;

	count = 0;
	count += ft_int_putstr_fd("0x", fd);
	count += ft_int_putptr_base_fd(*(unsigned long long *)&nbr, LOWERHEX, fd);
	return (count);
}
