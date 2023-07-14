/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:11:42 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:24 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	ft_putptr_base_fd(unsigned long long nbr, char *base, int fd)
{
	unsigned long long	hexptr;
	size_t				baselen;

	hexptr = nbr;
	baselen = ft_strlen(base);
	if (hexptr >= baselen)
		ft_putptr_base_fd(hexptr / baselen, base, fd);
	ft_putchar_fd(base[hexptr % baselen], fd);
}

void	ft_putptr_fd(unsigned long long nbr, int fd)
{
	ft_putstr_fd("0x", fd);
	ft_putptr_base_fd(*(unsigned long long *)&nbr, LOWERHEX, fd);
}
