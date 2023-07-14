/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:22:03 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/13 19:36:28 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
