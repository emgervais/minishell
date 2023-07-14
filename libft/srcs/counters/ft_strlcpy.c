/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:06:18 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:46 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	length;

	a = 0;
	length = ft_strlen(src);
	if (dstsize > 0)
	{
		while (a + 1 < dstsize && src[a])
		{
			dst[a] = src[a];
			a++;
		}
		dst[a] = '\0';
	}
	return (length);
}
