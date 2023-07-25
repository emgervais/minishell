/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:32:20 by egervais          #+#    #+#             */
/*   Updated: 2023/07/24 21:10:48 by egervais         ###   ########.fr       */
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

char *env(t_env_var *list, int ac)
{
    t_env_var *temp;
    char *env2;
    char *tmp;

    temp = list;
    if(ac != 1)
        return (NULL);
    tmp = add_one_char(temp->key, '=', 0);
    env2 = ft_strjoin(tmp, temp->value);
    tmp = add_one_char(env2, '\n', 1);
    temp = temp->next;
    while(temp)
    {
        if(!tmp)
            return (NULL);
        env2 = ft_strjoin(tmp, temp->key);
        free(tmp);
        tmp = add_one_char(env2, '=', 1);
        env2 = ft_strjoin(tmp, temp->value);
        free(tmp);
        if(temp->next)
            tmp = add_one_char(env2, '\n', 1);
        else
            return(env2);
        temp = temp->next;
    }
    return (tmp);
}