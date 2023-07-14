/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putnbr_base_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:10:41 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:15:58 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_putnbr_base_fd(unsigned int nbr, char *base, int fd)
{
	int				count;
	unsigned int	hexnb;
	size_t			baselen;

	count = 0;
	hexnb = nbr;
	baselen = ft_strlen(base);
	if (hexnb >= baselen)
		count += ft_int_putnbr_base_fd(hexnb / baselen, base, fd);
	count += ft_int_putchar(base[hexnb % baselen]);
	return (count);
}
