/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:13:51 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:17:10 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*start;
	const char	*end;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > s1 && ft_strchr(set, *end))
		end--;
	if (start >= end)
		return (NULL);
	str = ft_substr(start, 0, end - start + 1);
	return (str);
}
