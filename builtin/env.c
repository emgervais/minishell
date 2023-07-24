/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:32:20 by egervais          #+#    #+#             */
/*   Updated: 2023/07/18 19:20:52 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char *add_one_char(char *s1, char c, int malloced)
{
    char *str;
    int i;

    if(!s1)
        return (NULL);
    i = 0;
    str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
    if(!str)
        return (NULL);
    while(s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    str[i++] = c;
    str[i] = '\0';
    if(malloced)
        free(s1);
    return (str);
}

char *env(char **envp, int ac)
{
    int i;
    char *temp;
    char *temp2;

    if(ac != 1)
        return (NULL);
    i = 1;
    temp = *envp;
    temp = add_one_char(temp, '\n', 0);
    while(envp[i])
    {
        if(!envp[i + 1])
        {
            temp2 = ft_strjoin(temp, "_=/usr/bin/env");
            i++;
        }
        else
            temp2 = ft_strjoin(temp, envp[i++]);
        free(temp);
        temp2 = add_one_char(temp2, '\n', 1);
        if(!temp2)
            return (NULL);
        temp = temp2;
    }
    return (temp);
}