/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:35:26 by fpolycar          #+#    #+#             */
/*   Updated: 2023/07/26 04:48:22 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// This function will get the value of the env_var
// It will return the value of the env_var
static char	*get_value(char *key, t_env_var *env_var)
{
	while (env_var)
	{
		if (!ft_strncmp(key, env_var->key, ft_strlen(key) + 1))
			return (env_var->value);
		env_var = env_var->next;
	}
	return ("");
}

// This function will expand the variables in the argument
// It will return the new argument
static char	*expand_arg(char *arg, t_env_var *env_var, char **keys)
{
	int		i;
	int		j;
	char	*new_arg;

	i = 0;
	j = 0;
	new_arg = ft_strdup("");
	while (arg[i] && new_arg && keys[j])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != '$' && arg[i + 1] != ' ')
		{
			new_arg = ft_strjoin(new_arg, get_value(keys[j], env_var));
			i += ft_strlen(keys[j++]) + 1;
		}
		else
			new_arg = ft_strjoin(new_arg, ft_substr(arg, i++, 1));
	}
	if (new_arg && arg[i])
		new_arg = ft_strjoin(new_arg, ft_substr(arg, i, ft_strlen(arg) - i));
	return (new_arg);
}

// This function will get the keys of the argument
// It will return the keys
static char	**get_keys(char *arg)
{
	int		i;
	int		j;
	char	**keys;

	i = 0;
	j = 0;
	keys = malloc(sizeof(char *) * (ft_count_word(arg, '$') + 1));
	if (!keys)
		return (NULL);
	keys[0] = ft_strdup("");
	while (arg[i] && keys[j])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != '$' && arg[i + 1] != ' ')
		{
			while (arg[i + 1] && arg[i + 1] != '$' && arg[i + 1] != ' ')
				keys[j] = add_one_char(keys[j], arg[++i], 1);
			keys[++j] = ft_strdup("");
		}
		i++;
	}
	if (keys[j])
		keys[j] = NULL;
	else
		return (NULL);
	return (keys);
}

// This function will expand the variables in the arguments
// It will return the new arguments
static char	**expand_args(char **args, t_env_var *env_var)
{
	int		i;
	char	**keys;

	i = 0;
	while (args[i])
	{
		keys = get_keys(args[i]);
		if (!keys)
			return (NULL);
		args[i] = expand_arg(args[i], env_var, keys);
		if (!args[i])
			return (NULL);
		ft_free_split(keys);
		i++;
	}
	return (args);
}

// This function will expand the variables in the cmds
// It will return the new cmds
t_cmds	*expander(t_cmds *cmds, t_env_var *env_var)
{
	t_cmds	*tmp;

	tmp = cmds;
	while (tmp)
	{
		tmp->args = expand_args(tmp->args, env_var);
		tmp = tmp->next;
	}
	return (cmds);
}