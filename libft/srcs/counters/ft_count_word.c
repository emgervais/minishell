/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:05:45 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:06:07 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_count_word(const char *str, const char c)
{
	size_t	a;
	size_t	count;

	a = 0;
	count = 0;
	while (str[a])
	{
		if (a == 0)
		{
			if (str[a] != c)
				count++;
		}
		else
		{
			if (str[a - 1] == c && str[a] != c)
				count++;
		}
		a++;
	}
	return (count);
}
