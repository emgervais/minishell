/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:44:19 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 18:34:33 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_str_replace(char *str, char *old, char *new, size_t len)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strnstr(str, old, len);
	if (!tmp)
		return (str);
	tmp2 = ft_substr(str, 0, tmp - str);
	tmp3 = ft_strjoin(tmp2, new);
	free(tmp2);
	tmp2 = ft_substr(str, tmp - str + ft_strlen(old), ft_strlen(str));
	free(str);
	str = ft_strjoin(tmp3, tmp2);
	free(tmp2);
	free(tmp3);
	return (str);
}
