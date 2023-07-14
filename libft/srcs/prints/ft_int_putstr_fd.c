/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_putstr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:11:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:12 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_int_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	else
		write (fd, s, ft_strlen(s));
	return (ft_strlen(s));
}
