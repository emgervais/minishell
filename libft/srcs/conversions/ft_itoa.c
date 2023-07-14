/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:36 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:16 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	size_t	a;

	nb = n;
	a = ft_count_char(nb);
	str = malloc(sizeof(char) * (a + 1));
	if (!str)
		return (NULL);
	str[a] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[a - 1] = '0' + (nb % 10);
		nb = nb / 10;
		a--;
	}
	return (str);
}
