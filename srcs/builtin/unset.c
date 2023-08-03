/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:22:23 by egervais          #+#    #+#             */
/*   Updated: 2023/08/02 12:49:22 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int unset(t_env_var *env, char **var)
{
    t_env_var *temp;
    t_env_var *prev;
    int i;

    i = -1;
    while(var[++i])
    {
        temp = env;
        prev = env;
        while(temp && ft_strncmp(temp->key, *var, ft_strlen(*var)))
        {
            if(temp != prev)
                prev = prev->next;
            temp = temp->next;
        }
        if(temp)
        {
            prev->next = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    return (SUCCESS);
}