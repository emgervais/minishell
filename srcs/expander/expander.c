/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:35:26 by fpolycar          #+#    #+#             */
/*   Updated: 2023/08/18 18:55:35 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Remove the single quotes from the argument
char	**remove_single_quotes(char **args)
{
	int		i;
	int		j;
	char	*new_arg;

	i = 0;
	while (args[i])
	{
		j = 0;
		new_arg = ft_strdup("");
		while (args[i][j])
		{
			if (args[i][j] == '\'')
				j++;
			else
				new_arg = add_one_char(new_arg, args[i][j++], 1);
		}
		free(args[i]);
		args[i] = new_arg;
		i++;
	}
	return (args);
}

char	*skip_quotes(char *arg, int *i)
{
	if (arg[*i] == '\'')
	{
		(*i)++;
		while (arg[*i] && arg[*i] != '\'')
			(*i)++;
	}
	return (arg);
}


// This function will get the value of the env_var
// It will return the value of the env_var
char	*get_env_var_value(char *key, t_env_var *env_var)
{
	if (!ft_strncmp(key, "?", 2))
		return (ft_itoa(minishell()->status));
	while (env_var)
	{
		if (!ft_strncmp(key, env_var->key, ft_strlen(key) + 1))
			return (env_var->value);
		env_var = env_var->next;
	}
	return ("");
}

// This function will expand the variables in the argument
// It will return the new argument or NULL when failing
static char	*expand_arg(char *arg, t_env_var *env_var, char **keys)
{
	int		i;
	int		j;
	char	*new_arg;

	i = 0;
	j = 0;
	new_arg = ft_strdup("");
	while (new_arg && arg[i] && keys[j])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != '$' && arg[i + 1] != ' ')
		{
			new_arg = ft_strjoinfree(new_arg, get_env_var_value(keys[j], env_var), 1);
			i += ft_strlen(keys[j++]) + 1;
		}
		else if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '$')
			i++;
		else
			new_arg = add_one_char(new_arg, arg[i++], 1);
	}
	while (new_arg && arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '$')
			i++;
		else
			new_arg = add_one_char(new_arg, arg[i++], 1);
	}
	return (new_arg);
}

// This function will get the keys of the argument
// It will return the keys or NULL if failing
static char	**get_keys(char *arg, int i, int j)
{
	char	**keys;

	keys = malloc(sizeof(char *) * (ft_count_word(arg, '$') + 1));
	if (!keys)
		return (NULL);
	keys[0] = ft_strdup("");
	while (arg[i] && keys[j])
	{
		if (arg[i] == '\'')
			arg = skip_quotes(arg, &i);
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '?')
		{
			keys[j] = ft_strdup("?");
			keys[++j] = ft_strdup("");
			i++;
		}
		else if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != '$' && arg[i + 1] != ' ' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
		{
			while (arg[i + 1] && arg[i + 1] != '$' && arg[i + 1] != ' ' && (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_'))
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
// It will return the new arguments or NULL when failing
char	**expand_args(char **args, t_env_var *env_var)
{
	int		i;
	char	**keys;

	i = 0;
	while (args[i])
	{
		if (args[i][0] != '\'')
		{
			keys = get_keys(args[i], 0, 0);
			if (!keys)
				return (NULL);
			args[i] = expand_arg(args[i], env_var, keys);
			if (!args[i])
			{
				ft_free_split(keys);
				return (NULL);
			}
			ft_free_split(keys);
		}
		i++;
	}
	return (remove_single_quotes(args));
}

