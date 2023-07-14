/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:59 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:22:39 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_unsplit(char **split, char c)
{
	char	*str;
	char	*tmp;
	int		a;

	a = 0;
	str = NULL;
	while (split[a])
	{
		tmp = split[a];
		split[a] = ft_strjoin(split[a], &c);
		free (tmp);
		a++;
	}
	a = 0;
	while (split[a])
	{
		tmp = str;
		str = ft_strnjoin(str, split[a], ft_strlen(split[a]));
		free (tmp);
		a++;
	}
	str[ft_strlen(str) - 2] = '\0';
	return (str);
}
