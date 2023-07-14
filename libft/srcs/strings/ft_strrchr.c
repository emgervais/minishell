/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:43 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:13:46 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = ft_strlen(s);
	while (a > 0)
	{
		if (s[a] == (char)c)
			return ((char *)&s[a]);
		a--;
	}
	if (s[a] == (char)c)
		return ((char *)&s[a]);
	return (0);
}
