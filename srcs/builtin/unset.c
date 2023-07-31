/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:22:23 by egervais          #+#    #+#             */
/*   Updated: 2023/07/31 18:33:16 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void unset(t_env_var *env, char **var)
{
    t_env_var *temp;
    t_env_var *prev;
    int i;

    i = -1;
    while(var[++i])
    {
        temp = env;
        prev = env;
        while(temp && ft_strncmp(temp->key, var, ft_strlen(var)))
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
}