/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putnbr_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:10:46 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:01 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_putnbr_base(unsigned int nbr, char *base)
{
	int				count;
	unsigned int	hexnb;
	size_t			baselen;

	count = 0;
	hexnb = nbr;
	baselen = ft_strlen(base);
	if (hexnb >= baselen)
		count += ft_int_putnbr_base(hexnb / baselen, base);
	count += ft_int_putchar(base[hexnb % baselen]);
	return (count);
}
