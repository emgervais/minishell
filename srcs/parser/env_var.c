/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:55:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/20 22:36:39 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_var    *init_env_var(char *key, char *value)
{
    t_env_var    *env_var;

    env_var = (t_env_var *)malloc(sizeof(t_env_var));
    if (!env_var)
        return (NULL);
    env_var->key = ft_strdup(key);
    if (!env_var->key)
    {
        free(env_var);
        return (NULL);
    }
    env_var->value = ft_strdup(value);
    if (!env_var->value)
    {
        free(env_var->key);
        free(env_var);
        return (NULL);
    }
    env_var->next = NULL;
    return (env_var);
}

static int  add_env_var(t_env_var **env_var, t_env_var *new_env_var)
{
    t_env_var    *tmp;

    if (!*env_var)
    {
        *env_var = new_env_var;
        return (SUCCESS);
    }
    tmp = *env_var;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_env_var;
    return (SUCCESS);
}

t_env_var    *init_env_var_list(char **str)
{
    t_env_var   *env_var;
    t_env_var   *new_env_var;
    int         i;

    env_var = NULL;
    i = 0;
    while (str[i])
    {
        if (ft_strchr(str[i], '='))
        {
            new_env_var = init_env_var(ft_substr(str[i], 0, ft_strchr(str[i], '=') - str[i]), ft_strchr(str[i], '=') + 1);
            if (!new_env_var)
            {
                free_all_env_vars(env_var);
                return (NULL);
            }
            if (add_env_var(&env_var, new_env_var))
            {
                free_all_env_vars(env_var);
                return (NULL);
            }
        }
        i++;
    }
    return (env_var);
}