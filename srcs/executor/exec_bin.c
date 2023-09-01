/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:47:10 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 19:23:30 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory(t_cmds *cmds)
{
	struct stat	sb;

	if (stat(cmds->args[0], &sb) == -1)
		return (0);
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmds->args[0], STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		cmds->fd.status = 126;
		return (1);
	}
	return (0);
}

static char	*path_builder(char *path_cmd, char *cmd, t_env_var *env_var)
{
	char	**path;
	int		i;

	path = ft_split(get_env_var_value("PATH", env_var), ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], "/");
		if (!path_cmd)
			return (ft_free_split(path), NULL);
		path_cmd = ft_strjoinfree(path_cmd, cmd, 1);
		if (!path_cmd)
			return (ft_free_split(path), NULL);
		if (access(path_cmd, X_OK) != -1)
			return (ft_free_split(path), path_cmd);
		free(path_cmd);
		i++;
	}
	ft_free_split(path);
	return (NULL);
}

static char	*get_path(char *cmd, t_env_var *env_var, t_cmds *cmds)
{
	char	*path_cmd;

	path_cmd = NULL;
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (is_directory(cmds))
			return (NULL);
		path_cmd = ft_strdup(cmd);
		if (!path_cmd)
			return (NULL);
		if (access(path_cmd, X_OK) == -1)
			return (error_path(cmds, path_cmd, strerror(errno)));
		return (path_cmd);
	}
	path_cmd = path_builder(path_cmd, cmd, env_var);
	if (path_cmd)
		return (path_cmd);
	return (error_path(cmds, cmd, "command not found"));
}

static char	**env_var_to_array(t_env_var *env_var)
{
	char	**env;
	int		i;

	env = (char **)malloc(sizeof(char *) * (env_var_len(env_var) + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env_var)
	{
		env[i] = ft_strjoin(env_var->key, "=");
		env[i] = ft_strjoinfree(env[i], env_var->value, 1);
		if (!env[i])
			return (ft_free_split(env), NULL);
		env_var = env_var->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	exec_bin(t_cmds *cmds, t_minishell *mini)
{
	char	*path_cmd;
	char	**env;
	int		ret;

	ret = 0;
	path_cmd = get_path(cmds->args[0], mini->env_var, cmds);
	if (!path_cmd)
		return (cmds->fd.status);
	env = env_var_to_array(mini->env_var);
	if (!env)
		return (free(path_cmd), error_fd(1, cmds, 0));
	cmds->fd.pid = fork();
	if (cmds->fd.pid == -1)
		return (free(path_cmd), error_fd(1, cmds, 0));
	if (cmds->fd.pid == 0)
	{
		if (dup_fd(cmds) == ERROR)
			return (free(path_cmd), ft_free_split(env), error_fd(1, cmds, 0));
		if (execve(path_cmd, cmds->args, env) == -1)
			return (free(path_cmd), ft_free_split(env), error_fd(1, cmds, 0));
	}
	free(path_cmd);
	ft_free_split(env);
	return (ret);
}
