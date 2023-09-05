/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/09/05 12:38:17 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	error_cd(t_cmds *cmd, int is_home)
{
	if (is_home)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (ERROR);
}

static int	change_dir(char *path, t_cmds *cmd)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (error_cd(cmd, 0));
	if (S_ISDIR(buf.st_mode))
	{
		if (chdir(path) == -1)
			return (error_cd(cmd, 0));
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	cd(t_cmds *cmd, t_env_var *env_var)
{
	char	*path;

	if (set_env_var("OLDPWD", getcwd(NULL, 0), env_var))
		return (ERROR);
	if (cmd->argc == 1 || ft_strncmp(cmd->args[1], "~", 2) == 0)
		path = get_env_var_value("HOME", env_var);
	else
	{
		if (ft_strncmp(cmd->args[1], "", 1) == 0)
			path = get_env_var_value("HOME", env_var);
		else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
			path = get_env_var_value("OLDPWD", env_var);
		else
			path = cmd->args[1];
	}
	if (change_dir(path, cmd) == ERROR)
		return (ERROR);
	if (set_env_var("PWD", getcwd(NULL, 0), env_var))
		return (ERROR);
	return (SUCCESS);
}
