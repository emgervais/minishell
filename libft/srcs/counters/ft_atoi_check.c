/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:05:27 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:36 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_atoi_check(const char *str, int *negative)
{
	int	a;

	a = 0;
	while (str[a] && (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13)))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			*negative = -1;
		a++;
	}
	return (a);
}
