/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:12:30 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:32 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_gnl_join(int fd)
{
	char	*str;
	char	*gnl;

	str = NULL;
	gnl = NULL;
	while (fd > -1)
	{
		gnl = get_next_line(fd);
		if (!gnl)
		{
			free (gnl);
			return (str);
		}
		if (!str)
			str = gnl;
		else
			str = ft_strfreejoin(str, gnl);
		if (!str)
			return (NULL);
	}
	return (NULL);
}
