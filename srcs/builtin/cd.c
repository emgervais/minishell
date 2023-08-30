/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/29 22:23:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	error_cd(t_cmds *cmd)
{
	if (cmd->argc == 1)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	cmd->e_status = 1;
	return (1);
}

int	cd(t_cmds *cmd, t_env_var *env_var)
{
	char *path;

	if (set_env_var("OLDPWD", getcwd(NULL, 0), env_var))
		return (ERROR);
	if (cmd->argc == 1 || ft_strncmp(cmd->args[1], "~", 2) == 0)
		path = get_env_var_value("HOME", env_var);
	else
	{
		if (ft_strncmp(cmd->args[1], "", 1) == 0 || get_env_var_value("PWD",
				env_var) == NULL)
			path = get_env_var_value("HOME", env_var);
		else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
			path = get_env_var_value("OLDPWD", env_var);
		else
			path = cmd->args[1];
	}
	if (chdir(path) == -1)
	{
		if (cmd->argc == 1)
			return (error_cd(cmd));
		else
			return (error_cd(cmd));
	}
	if (set_env_var("PWD", getcwd(NULL, 0), env_var))
		return (ERROR);
	cmd->e_status = 0;
	return (0);
}