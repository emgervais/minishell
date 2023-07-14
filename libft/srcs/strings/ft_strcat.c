/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:12:59 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:47 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcat(char *dst, const char *src)
{
	int	a;
	int	b;

	if (!dst || !src)
		return (NULL);
	a = ft_strlen(dst);
	b = 0;
	while (src[b])
	{
		dst[a + b] = src[b];
		b++;
	}
	dst[a + b] = '\0';
	return (dst);
}
