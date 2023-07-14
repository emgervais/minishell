/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:11 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:13:59 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_add_str_to_int(const char *str, int *a)
{
	long	result;

	result = 0;
	while (ft_isdigit(str[*a]))
	{
		result = result * 10 + str[*a] - '0';
		(*a)++;
	}
	return (result);
}
