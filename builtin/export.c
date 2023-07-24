/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:56:47 by egervais          #+#    #+#             */
/*   Updated: 2023/07/20 23:06:38 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (1);
	return (0);
}
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

char	*ft_strdu(const char *s1)
{
	int		a;
	int		b;
	char	*s2;

	a = ft_strlen(s1);
	b = 0;
	s2 = malloc(sizeof(char) * (a + 1));
	if (!s2)
		return (NULL);
	while (b < a)
	{
		s2[b] = s1[b];
		b++;
	}
	s2[b] = '\0';
	return (s2);
}

bool is_var_valid(char *str)
{
    int i;

    i = 1;
    if(!ft_isalpha(str[0]) && str[0] != '_')
        return (1);
    while(str[i] && str[i] != '=')
    {
        if(!ft_isalnum(str[i]) && str[i] != '_')//if exist replace
            return (1);
        i++;
    }
    if(!str[i])
        return (1);
    return (0);
    
}
bool export(char **args, char **envp)
{
    int i;
    int l;
    int check;
    char *temp;

    i = 0;
    l = -1;
    while(envp[i])
        i++;
    if(is_var_valid(args[1]))
        return (0);
    temp = envp[i - 1];
    envp[i - 1] = ft_strdu(args[1]);
    envp[i++] = temp;
    envp[i] = NULL;
    return (0);
}

int main(int ac, char **av, char **envp)
{
    char *a[3] = {"export", "robert=telephone", NULL};

    int i = export(a, envp);
    int l = 0;

    printf("value %d\n", i);
    while(envp[l])
        printf("%s\n", envp[l++]);
}