/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:22:23 by egervais          #+#    #+#             */
/*   Updated: 2023/08/29 22:24:30 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	unset_wrong_usage(t_cmds *cmd, int i)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(cmd->args[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

void	delete_env_var(char *key, t_env_var *env_var)
{
	t_env_var	*tmp;
	t_env_var	*prev;

	tmp = env_var;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key) + 1) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				env_var = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset(t_cmds *cmd, t_env_var *env_var)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
			return (unset_wrong_usage(cmd, i));
		delete_env_var(cmd->args[i], env_var);
		i++;
	}
	return (0);
}
