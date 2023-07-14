/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:06 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:52 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	a;
	size_t	b;

	if (!dst || !src)
		return (NULL);
	a = ft_strlen(src);
	b = 0;
	while (b < a)
	{
		dst[b] = src[b];
		b++;
	}
	dst[b] = '\0';
	return (dst);
}
