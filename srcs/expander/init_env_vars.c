/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:55:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 15:03:58 by ele-sage         ###   ########.fr       */
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
// It will return the new env_var
t_env_var	*new_env_var(char *key, char *value)
{
    t_env_var	*env_var;

    env_var = (t_env_var *)malloc(sizeof(t_env_var));
    if (!env_var)
        return (NULL);
    env_var->key = ft_substr(key, 0, ft_int_strchr(key, '='));
    env_var->value = ft_strdup(value);
    env_var->next = NULL;
    return (env_var);
}

// This function will add a new env_var to the env_var list
// It will return SUCCESS or ERROR
int	add_env_var(t_env_var *env_var, char *envp)
{
    t_env_var	*tmp;
    t_env_var	*new;

    tmp = env_var;
    while (tmp->next)
        tmp = tmp->next;
    new = new_env_var(envp, ft_strchr(envp, '=') + 1);
    if (!new)
        return (ERROR);
    tmp->next = new;
    return (SUCCESS);
}

// This function will initialize the env_var list
// It will return SUCCESS or ERROR
static int	init_env_var_list(t_env_var *env_var, char **envp)
{
    int		i;

    i = 0;
    while (envp[i])
    {
        if (add_env_var(env_var, envp[i]) == ERROR)
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

// This function will initialize the env_var
t_env_var	*init_env_var(char **envp)
{
    t_env_var	*env_var;

    env_var = new_env_var(envp[0], ft_strchr(envp[0], '=') + 1);
    if (!env_var)
        return (NULL);
    if (init_env_var_list(env_var, envp) == ERROR)
        return (NULL);
	return (env_var);
}