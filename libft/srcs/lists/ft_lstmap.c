/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:27:15 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:00:21 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*firstlst;
	void	*content;

	firstlst = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		newlst = ft_lstnew(content);
		if (!newlst)
		{
			del(content);
			while (firstlst)
			{
				newlst = firstlst->next;
				del(firstlst->content);
				free(firstlst);
				firstlst = newlst;
			}
			return (NULL);
		}
		ft_lstadd_back(&firstlst, newlst);
		lst = lst->next;
	}
	return (firstlst);
}
