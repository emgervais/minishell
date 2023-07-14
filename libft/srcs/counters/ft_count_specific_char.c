/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_specific_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:05:39 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:34:34 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_count_specific_char(char *str, int c)
{
	int	count;
	int	a;

	count = 0;
	a = 0;
	while (str[a])
	{
		if (str[a] == c)
			count++;
		a++;
	}
	return (count);
}
