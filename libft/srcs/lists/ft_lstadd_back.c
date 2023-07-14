/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:06:54 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:06:57 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_back(t_list **lst, t_list *newlst)
{
	t_list	*last;

	last = NULL;
	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = newlst;
		}
		else
			*lst = newlst;
	}
}
