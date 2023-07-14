/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:10:08 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:15:44 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			a;
	unsigned char	*dest;
	unsigned char	*srce;

	if (!src && !dst)
		return (NULL);
	dest = dst;
	srce = src;
	a = 0;
	while (a < n)
	{
		dest[a] = srce[a];
		a++;
	}
	return (dst);
}
