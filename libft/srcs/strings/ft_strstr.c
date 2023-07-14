/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:48 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:17:08 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	a;
	size_t	b;

	if (!needle || !needle[0])
		return ((char *)haystack);
	a = 0;
	while (haystack[a])
	{
		b = 0;
		if (haystack[a] == needle[b])
		{
			while (haystack[a + b] == needle[b])
			{
				b++;
				if (!needle[b])
					return ((char *)&haystack[a]);
			}
		}
		a++;
	}
	return (NULL);
}
