/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:05:45 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 18:52:23 by egervais         ###   ########.fr       */
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

size_t	ft_count_word_array(const char **args, const char c)
{
	size_t	count;
	int		a;

	count = 0;
	a = 0;
	while (args[a])
	{
		count += ft_count_word(args[a], c);
		a++;
	}
	return (count);
}
