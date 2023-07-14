/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:10:15 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:15:47 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		a;

	if (!dst && !src)
		return (NULL);
	a = 0;
	if (dst <= src)
	{
		while (a < n)
		{
			((char *)dst)[a] = ((char *)src)[a];
			a++;
		}
	}
	else if (dst > src)
	{
		while (n > 0)
		{
			((char *)dst)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	return (dst);
}
