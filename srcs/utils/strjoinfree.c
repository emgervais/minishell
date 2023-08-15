/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:46:17 by egervais          #+#    #+#             */
/*   Updated: 2023/08/15 13:46:18 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void freejoin(const char *s1, const char *s2, int malloced)
{
    if(!malloced)
        return ;
    else if(malloced == 1)
        free(s1);
    else
    {
        free(s1);
        free(s2);
    }
}
//remake of strjoin but can free the passed strings
//malloced 1 to free first string, 2 to free both and 0 to not free them
char	*ft_strjoinfree(const char *s1, const char *s2, int malloced)
{
	char	*str;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	a = 0;
	b = 0;
	str = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[a])
	{
		str[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		str[a + b] = s2[b];
		b++;
	}
	str[a + b] = '\0';
    freejoin(s1, s2, malloced);
	return (str);
}