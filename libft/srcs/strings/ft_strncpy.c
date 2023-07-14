/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:17:03 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	a;

	a = 0;
	while (a < len && src[a])
	{
		dst[a] = src[a];
		a++;
	}
	while (a < len)
	{
		dst[a] = '\0';
		a++;
	}
	return (dst);
}
