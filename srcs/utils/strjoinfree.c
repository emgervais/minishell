/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:46:17 by egervais          #+#    #+#             */
/*   Updated: 2023/09/01 19:17:56 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	freejoin(const char *s1, const char *s2, int malloced)
{
	if (!malloced)
		return ;
	else if (malloced == 1)
		free((char *)s1);
	else
	{
		free((char *)s1);
		free((char *)s2);
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
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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

//remake of substr but can free the passed string
//malloced 1 to free string, 0 to not free it
char	*ft_substrfree(char const *s, unsigned int start, size_t len,
		int malloced)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	if (malloced)
		free((char *)s);
	return (str);
}

char	**remove_empty_args(char **args, int i, int j)
{
	char	**new_args;

	while (args[i])
	{
		if (ft_strlen(args[i]))
			j++;
		i++;
	}
	new_args = malloc(sizeof(char *) * (j + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0])
			new_args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	new_args[j] = NULL;
	free(args);
	return (new_args);
}
