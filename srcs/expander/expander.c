/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:35:26 by fpolycar          #+#    #+#             */
/*   Updated: 2023/07/24 18:35:28 by ele-sage         ###   ########.fr       */
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
	if (!new_arg)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != ' ')
		{
			new_arg = ft_strjoin(new_arg, get_value(keys[j], env_var));	
			if (!new_arg)
				return (NULL);
			i += ft_strlen(keys[j++]) + 1;
		}
		else
			new_arg = ft_strjoin(new_arg, ft_substr(arg, i++, 1));
	}
	return (new_arg);
}

static int dollar_count(char *arg)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != ' ')
			count++;
		i++;
	}
	return (count);
}

// This function will expand the variables in the arguments
// It will return the new arguments
static char	**expand_args(char **args, t_env_var *env_var)
{
	int		i;
	char	*tmp;
	char	**keys;

	i = 0;
	while (args[i])
	{
		tmp = args[i];
		keys = ft_split(args[i], '$');
		if (!keys)
			return (NULL);
		if (dollar_count(args[i]) == 0)
			args[i] = ft_strdup(args[i]);
		else if (dollar_count(args[i]) < (int) ft_splitlen(keys))
			args[i] = expand_arg(args[i], env_var, &keys[1]);
		else
			args[i] = expand_arg(args[i], env_var, keys);
		if (!args[i])
			return (NULL);
		free(tmp);
		free(keys);
		i++;
	}
	return (args);
}

static void	print_after_expander(t_cmds *cmds)
{
	t_cmds	*tmp;
	t_redir	*tmp_redir;

	tmp = cmds;
	while (tmp)
	{
		printf("args: ");
		for (int i = 0; tmp->args[i]; i++)
			printf("%s ", tmp->args[i]);
		printf("\n");
		printf("redir: ");
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			printf("%d %s ", tmp_redir->type, tmp_redir->file);
			tmp_redir = tmp_redir->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
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
	print_after_expander(cmds);
	return (cmds);
}