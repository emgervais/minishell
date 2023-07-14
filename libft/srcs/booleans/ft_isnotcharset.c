/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnotcharset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:03:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:03:32 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isnotcharset(char c, char *set)
{
	size_t	a;

	a = 0;
	while (set[a])
	{
		if (c == set[a])
			return (0);
		a++;
	}
	return (1);
}
