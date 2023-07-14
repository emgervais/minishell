/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_strrchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:12:51 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:43 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_strrchr(const char *s, int c)
{
	int	a;

	a = ft_strlen(s);
	while (a > 0)
	{
		if (s[a] == (char)c)
			return (a);
		a--;
	}
	if (s[a] == (char)c)
		return (a);
	return (-1);
}
