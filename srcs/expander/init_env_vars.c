/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:55:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/28 22:49:12 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will return the length of the env_var list
int env_var_len(t_env_var *env_var)
{
    int     len;

    len = 0;
    while (env_var)
    {
        env_var = env_var->next;
        len++;
    }
    return (len);
}

// This function will create a new env_var
// It will return the new env_var or nULL if failing
t_env_var	*new_env_var(char *key_value)
{
    t_env_var	*env_var;

    env_var = (t_env_var *)malloc(sizeof(t_env_var));
    if (!env_var)
        return (NULL);
    env_var->key = ft_substr(key_value, 0, ft_int_strchr(key_value, '='));
    if (!env_var->key)
    {
        free(env_var);
        return (NULL);
    }
    env_var->value = ft_strdup(ft_strchr(key_value, '=') + 1);
    if (!env_var->value)
    {
        free(env_var);
        free(env_var->key);
        return (NULL);
    }
    env_var->next = NULL;
    return (env_var);
}

// This function will add a new env_var to the env_var list
// It will return SUCCESS or ERROR
int	add_env_var(t_env_var *env_var, char *key_value)
{
    t_env_var	*tmp;
    t_env_var	*new;

    tmp = env_var;
    while (tmp->next)
        tmp = tmp->next;
    new = new_env_var(key_value);
    if (!new)
        return (ERROR);
    tmp->next = new;
    return (SUCCESS);
}

// This function will search for the env_var with the key
// if it finds it, it will set the value
// if it doesn't find it, it will create a new env_var
//returns NULL if failing
int  set_env_var(char *key, char *value, t_env_var *env_var)
{
    t_env_var	*tmp;
    char        *key_value;

    tmp = env_var;
    if(!key)
        return (ERROR);
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            if(!tmp->value)
                return (ERROR);
            return (SUCCESS);
        }
        tmp = tmp->next;
    }
    key_value = ft_strjoinfree(add_one_char(key, '=', 0), value, 0);
    if (!key_value)
        return (ERROR);
    if (add_env_var(env_var, key_value) == ERROR)
        return (ERROR);
    free(key_value);
    return (SUCCESS);
}

// This function will initialize the env_var
t_env_var	*init_env_var(char **envp)
{
    t_env_var	*env_var;
    int			i;

    i = 0;
    env_var = new_env_var(envp[i]);
    if (!env_var)
        return (NULL);
    while (envp[++i])
    {
        if (add_env_var(env_var, envp[i]) == ERROR)
            return (NULL);
    }
    return (env_var);
}