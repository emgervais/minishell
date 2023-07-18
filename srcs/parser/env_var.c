/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:55:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/18 17:37:17 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_var_value(char *var, t_cmds *cmds)
{
	t_cmds	*tmp;
	int		i;
	char	*value;

	tmp = cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			if (ft_strncmp(tmp->args[i], var, ft_strlen(var)) == 0)
			{
				value = ft_strdup(tmp->args[i] + ft_strlen(var) + 1);
				return (value);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char	**is_env_var(char *str)
{
	int	i;
	int count;
	char	**env_var;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return (NULL);
	env_var = ft_split(str, '$');
	if (!env_var)
		return (NULL);
	return (&env_var[ft_splitlen(env_var) - count]);	
}

void	replace_env_var(t_cmds *commands)
{
	t_cmds	*tmp;
	t_cmds	*tmp2;
	int		i;
	int		j;
	char	**env_var;
	char	*value;

	tmp = commands;
	tmp2 = commands;
	while (tmp)
	{
		i = 0;
		while (i < tmp->argc)
		{
			env_var = is_env_var(tmp->args[i]);
			if (env_var)
			{
				j = 0;
				while (env_var[j])
				{
					value = get_env_var_value(env_var[j], tmp2);
					if (value)
					{
						free(tmp->args[i]);
						tmp->args[i] = value;
					}
					j++;
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
