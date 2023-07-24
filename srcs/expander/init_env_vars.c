/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:55:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/24 15:45:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will create a new env_var
// It will return the new env_var
t_env_var	*new_env_var(char *key, char *value)
{
    t_env_var	*env_var;

    env_var = (t_env_var *)malloc(sizeof(t_env_var));
    if (!env_var)
        return (NULL);
    env_var->key = ft_strdup(key);
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

	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->key = NULL;
	env_var->value = NULL;
	env_var->next = NULL;
	if (init_env_var_list(env_var, envp) == ERROR)
		return (NULL);
	return (env_var);
}