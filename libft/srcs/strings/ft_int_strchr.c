/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_strchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:12:47 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:41 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_strchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (s[a])
	{
		if (s[a] == (char)c)
			return (a);
		a++;
	}
	if (s[a] == (char)c)
		return (a);
	return (-1);
}
