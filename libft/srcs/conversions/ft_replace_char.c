/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:40 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:18 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_replace_char(char *str, char c, char rep)
{
	int	a;

	a = 0;
	if (!str || !c || !rep)
		return ;
	while (str[a])
	{
		if (str[a] == c)
			str[a] = rep;
		a++;
	}
	return ;
}
