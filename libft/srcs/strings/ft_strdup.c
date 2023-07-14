/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:09 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:54 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	int		a;
	int		b;
	char	*s2;

	a = ft_strlen(s1);
	b = 0;
	s2 = malloc(sizeof(char) * (a + 1));
	if (!s2)
		return (NULL);
	while (b < a)
	{
		s2[b] = s1[b];
		b++;
	}
	s2[b] = '\0';
	return (s2);
}
