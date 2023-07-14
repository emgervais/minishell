/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:22 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:59 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	size_t	a;
	size_t	b;

	if (!dst || !src)
		return (NULL);
	if (len == 0)
		return (dst);
	a = ft_strlen(dst);
	b = 0;
	while (src[b] && b < len)
	{
		dst[a + b] = src[b];
		b++;
	}
	dst[a + b] = '\0';
	return (dst);
}
