/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfreejoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:55 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strfreejoin(const char *s1, const char *s2)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	if (!s1 || !s2)
		return (NULL);
	tmp1 = (char *)s1;
	tmp2 = (char *)s2;
	str = ft_strjoin(s1, s2);
	free (tmp1);
	free (tmp2);
	return (str);
}
