/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:29:11 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/21 16:56:03 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *get_env_var_value(char *key, t_env_var *env_var)
{
    int i;
    t_env_var *tmp;

    tmp = env_var;
    while (env_var)
    {
        i = 0;
        while (key[i] && tmp->key[i] && key[i] == tmp->key[i])
            i++;
        if (key[i] == '\0' && tmp->key[i] == '\0')
            return (tmp->value);
        env_var = tmp->next;
    }
    return (NULL);
}

static char *get_all_vars_value(int amount, char **keys, t_env_var *env_var, char *new_str)
{
    int i;
    char *value;

    i = 0;
    if ((int)ft_splitlen(keys) != amount)
    {
        i = 1;
        amount = ft_splitlen(keys);
        new_str = ft_strdup(keys[0]);
        if (!new_str)
            return (NULL);
    }
    while (keys[i])
    {
        value = get_env_var_value(keys[i], env_var);
        if (value)
        {
            if (new_str)
                new_str = ft_strjoin(new_str, value);
            else
                new_str = ft_strdup(value);    
            if (!new_str)
                return (NULL);
        }
        i++;
    }
    if (!new_str)
        new_str = ft_strdup("");
    return (new_str);
}

static int  amount_of_env_vars(char *str)
{
    int i;
    int amount;

    i = 0;
    amount = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] != '$')
            amount++;
        i++;
    }
    return (amount);
}

int replace_env_vars(char **str, t_env_var *env_var)
{
    char        **keys;
    char        *new_str;
    int         i;
    int         amount;

    i = 0;
    new_str = NULL;
    while (str[i])
    {
        amount = amount_of_env_vars(str[i]);
        if (amount)
        {
            if (str[i][0] != '\'')
            {
                keys = ft_split(str[i], '$');
                if (!keys)
                    return (ERROR);
                free(str[i]);
                str[i] = get_all_vars_value(amount, keys, env_var, new_str);
                free(keys);
                if (!str[i])
                    return (ERROR);
            }
        }
        i++;
    }
    return (SUCCESS);
}
