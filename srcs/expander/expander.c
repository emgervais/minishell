/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:35:26 by fpolycar          #+#    #+#             */
/*   Updated: 2023/09/01 18:49:33 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*fill_after_expand(char *arg, char *new_arg, int *i)
{
	while (arg[*i])
	{
		if (arg[*i] == '$' && arg[*i + 1] && arg[*i + 1] == '$')
			(*i)++;
		else
			new_arg = add_one_char(new_arg, arg[(*i)++], 1);
	}
	free(arg);
	return (new_arg);
}

// This function will expand the variables in the argument
// It will return the new argument or NULL when failing
char	*expand_arg(char *arg, t_env_var *env_var, char **keys)
{
	int		i;
	int		j;
	char	*new_arg;

	i = 0;
	j = 0;
	new_arg = ft_strdup("");
	while (new_arg && arg[i] && keys[j])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != '$' && arg[i
			+ 1] != ' ')
		{
			new_arg = ft_strjoinfree(new_arg, get_env_var_value(keys[j],
									env_var), 1);
			i += ft_strlen(keys[j++]) + 1;
		}
		else if (arg[i] == '$' && arg[i + 1] && arg[i + 1] == '$')
			i++;
		else
			new_arg = add_one_char(new_arg, arg[i++], 1);
	}
	new_arg = fill_after_expand(arg, new_arg, &i);
	return (new_arg);
}

static void	retrieve_keys(char **keys, char *arg, int *i, int *j)
{
	int	dquote;

	dquote = 0;
	while (arg[*i] && keys[*j])
	{
		if (arg[*i] == '\"')
			dquote = !dquote;
		if (arg[*i] == '\'' && !dquote)
			arg = skip_quotes(arg, i);
		if (arg[*i] == '$' && arg[*i + 1] && arg[*i + 1] == '?')
		{
			keys[*j] = add_one_char(keys[*j], '?', 1);
			keys[++(*j)] = ft_strdup("");
			(*i)++;
		}
		else if (arg[*i] == '$' && arg[*i + 1] && arg[*i + 1] != '$' && arg[*i
			+ 1] != ' ' && (ft_isalpha(arg[*i + 1]) || arg[*i + 1] == '_'))
		{
			while (arg[*i + 1] && arg[*i + 1] != '$' && arg[*i + 1] != ' '
				&& (ft_isalpha(arg[*i + 1]) || arg[*i + 1] == '_'))
				keys[*j] = add_one_char(keys[*j], arg[++(*i)], 1);
			keys[++(*j)] = ft_strdup("");
		}
		(*i)++;
	}
}

// This function will get the keys of the argument
// It will return the keys or NULL if failing
char	**get_keys(char *arg, int i, int j)
{
	char	**keys;

	keys = malloc(sizeof(char *) * (ft_count_word(arg, '$') + 1));
	if (!keys)
		return (NULL);
	keys[0] = ft_strdup("");
	if (!keys[0])
		return (NULL);
	retrieve_keys(keys, arg, &i, &j);
	if (keys[j])
	{
		free(keys[j]);
		keys[j] = NULL;
		return (keys);
	}
	free(keys[0]);
	free(keys);
	return (NULL);
}

static char	**remove_empty_args(char **args, int i, int j)
{
	char	**new_args;

	while (args[i])
	{
		if (ft_strlen(args[i]))
			j++;
		i++;
	}
	new_args = malloc(sizeof(char *) * (j + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0])
			new_args[j++] = args[i];
		i++;
	}
	new_args[j] = NULL;
	free(args);
	return (new_args);
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
		i++;
	}
	args = remove_empty_args(args, 0, 0);
	if (!args)
		return (NULL);
	args = remove_quotes(args);
	return (args);
}
