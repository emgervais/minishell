/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:35:26 by fpolycar          #+#    #+#             */
/*   Updated: 2023/07/24 14:02:00 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function will expand the variables in the argument
// It will return the new argument
static char	*expand_arg(char *arg, t_env_var *env_var)
{
	int		i;
	int		j;
	char	*new_arg;
	char	*tmp;

	i = 0;
	j = 0;
	new_arg = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!new_arg)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			tmp = new_arg;
			new_arg = ft_strjoin(new_arg, get_env_var(arg, &i, env_var));
			free(tmp);
		}
		else
			new_arg[j++] = arg[i++];
	}
	new_arg[j] = '\0';
	return (new_arg);
}

// This function will expand the variables in the arguments
// It will return the new arguments
static char	**expand_args(char **args, t_env_var *env_var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		tmp = args[i];
		args[i] = expand_arg(args[i], env_var);
		free(tmp);
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

