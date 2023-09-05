/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:56:47 by egervais          #+#    #+#             */
/*   Updated: 2023/09/05 09:35:33 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_export(t_env_var *env_var, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env_var->key, fd);
	if (env_var->value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(env_var->value, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
}

static int	export_no_arg(t_env_var *env_var, t_cmds *cmd)
{
	if (!ft_strlen(get_env_var_value("OLDPWD", env_var)))
		ft_putstr_fd("declare -x OLDPWD\n", cmd->fd.fd_out);
	while (env_var)
	{
		if (env_var->value)
			print_export(env_var, cmd->fd.fd_out);
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
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int	export(t_cmds *cmd, t_env_var *env_var)
{
	int	i;

	i = 1;
	if (cmd->argc == 1)
		return (export_no_arg(env_var, cmd));
	if (cmd->next || cmd->prev)
		return (ERROR);
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
			return (export_wrong_usage(cmd, i));
		if (ft_strchr(cmd->args[i], '='))
		{
			if (set_env_var(ft_substr(cmd->args[i], 0,
						ft_int_strchr(cmd->args[i], '=')),
					ft_strchr(cmd->args[i], '=') + 1, env_var))
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
