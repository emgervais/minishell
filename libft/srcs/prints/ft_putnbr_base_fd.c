/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:11:33 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_base_fd(unsigned int nbr, char *base, int fd)
{
	unsigned int	hexnb;
	size_t			baselen;

	hexnb = nbr;
	baselen = ft_strlen(base);
	if (hexnb >= baselen)
		ft_putnbr_base_fd(hexnb / baselen, base, fd);
	ft_putchar_fd(base[hexnb % baselen], fd);
}
