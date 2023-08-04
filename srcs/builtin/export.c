/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:56:47 by egervais          #+#    #+#             */
/*   Updated: 2023/08/04 10:46:04 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


static int	export_no_arg(t_env_var *env_var)
{
	while(env_var)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_var->key, STDOUT_FILENO);
		if(env_var->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_var->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env_var = env_var->next;
	}
	return (SUCCESS);
}

static int	export_wrong_usage(t_cmds *cmd, int i)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd->args[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (ERROR);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int export(t_cmds *cmd, t_env_var *env_var)
{
	int	i;

	i = 1;
	if (cmd->argc == 1)
		return (export_no_arg(env_var));
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
			return (export_wrong_usage(cmd, i));
		if (ft_strchr(cmd->args[i], '='))
			set_env_var(ft_substr(cmd->args[i], 0, ft_int_strchr(cmd->args[i], '=')),//protect
			ft_strchr(cmd->args[i], '=') + 1, env_var);
		else
			set_env_var(cmd->args[i], "", env_var);//protect
		i++;
	}
	return (SUCCESS);
}