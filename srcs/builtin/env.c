/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:32:20 by egervais          #+#    #+#             */
/*   Updated: 2023/08/02 12:39:44 by ele-sage         ###   ########.fr       */
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

int env(t_env_var *list, int ac)
{
    t_env_var *temp;

    temp = list;
    if(ac > 1)
    {
        ft_putendl_fd("env: too many arguments", STDERR_FILENO);
        return (ERROR);
    }
    while(temp)
    {
        ft_putstr_fd(temp->key, STDOUT_FILENO);
        ft_putchar_fd('=', STDOUT_FILENO);
        ft_putendl_fd(temp->value, STDOUT_FILENO);
        temp = temp->next;
    }
    return (SUCCESS);
}