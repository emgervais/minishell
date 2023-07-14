/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:34 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:13:37 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnjoin(const char *s1, const char *s2, ssize_t index)
{
	char	*str;
	int		a;
	int		b;

	if (!s1 && !s2)
		return (NULL);
	a = 0;
	b = 0;
	str = malloc (sizeof(char) * (ft_strlen(s1) + index + 1));
	if (!str)
		return (NULL);
	while (s1[a])
	{
		str[a] = s1[a];
		a++;
	}
	while (b < index)
	{
		str[a + b] = s2[b];
		b++;
	}
	str[a + b] = '\0';
	return (str);
}
