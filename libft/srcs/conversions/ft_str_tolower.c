/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:04:44 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:14:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_str_tolower(const char *str)
{
	char	*newstr;
	int		a;
	int		len;

	a = 0;
	len = ft_strlen(str);
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (a < len)
	{
		if (ft_isupper(str[a]))
			newstr[a] = ft_tolower(str[a]);
		else
			newstr[a] = str[a];
		a++;
	}
	newstr[a] = '\0';
	return (newstr);
}
