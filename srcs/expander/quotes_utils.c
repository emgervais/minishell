/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:49:09 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 19:27:10 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes_arg(char *args, char *new_arg)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while (args[i])
	{
		if (args[i] == '\"' && squote == 0)
		{
			i++;
			dquote = !dquote;
		}
		else if (args[i] == '\'' && dquote == 0)
		{
			squote = !squote;
			i++;
		}
		else
			new_arg = add_one_char(new_arg, args[i++], 1);
	}
	return (new_arg);
}

// Remove the single quotes and double quotes from the arguments
char	**remove_quotes(char **args)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (args[i])
	{
		new_arg = ft_strdup("");
		if (!new_arg)
			return (NULL);
		new_arg = remove_quotes_arg(args[i], new_arg);
		if (!new_arg)
			return (NULL);
		free(args[i]);
		args[i] = new_arg;
		i++;
	}
	return (args);
}

int	remove_quotes_redir(t_redir *redir)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (redir)
	{
		new_arg = ft_strdup("");
		if (!new_arg)
			return (ERROR);
		new_arg = remove_quotes_arg(redir->file, new_arg);
		if (!new_arg)
			return (ERROR);
		free(redir->file);
		redir->file = new_arg;
		redir = redir->next;
	}
	return (SUCCESS);
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
