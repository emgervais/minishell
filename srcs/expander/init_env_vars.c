/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:55:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/08 14:06:31 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_len(t_env_var *env_var)
{
	int	len;

	len = 0;
	while (env_var)
	{
		env_var = env_var->next;
		len++;
	}
	return (len);
}

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

int	set_env_var(char *key, char *value, t_env_var *env_var)
{
	t_env_var	*tmp;
	char		*key_value;

	tmp = env_var;
	if (!key)
		return (ERROR);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			if (!tmp->value)
				return (free(key), ERROR);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	key_value = ft_strjoinfree(add_one_char(key, '=', 1), value, 1);
	if (!key_value)
		return (ERROR);
	if (add_env_var(env_var, key_value) == ERROR)
		return (free(key_value), ERROR);
	free(key_value);
	return (SUCCESS);
}

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
