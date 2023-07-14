/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:06:12 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:44 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	b;
	size_t	srclen;

	a = ft_strlen(dst);
	b = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= a)
		return (dstsize + srclen);
	while (dstsize && (--dstsize - a) && src[b])
	{
		dst[a + b] = src[b];
		b++;
	}
	dst[a + b] = '\0';
	return (srclen + a);
}
