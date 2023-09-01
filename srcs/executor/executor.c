/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 16:10:49 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_child(t_minishell *mini)
{
	int	status;
	t_cmds	*cmds;

	cmds = mini->cmds;
	status = 0;
	while (cmds)
	{
		if (cmds->fd.pid != 0 && cmds->fd.pid != -1)
		{
			waitpid(cmds->fd.pid, &status, 0);
			if (WIFEXITED(status) > mini->status && cmds->builtin == NO_BUILTIN)
				mini->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && cmds->builtin == NO_BUILTIN)
				mini->status = WTERMSIG(status) + 128;
		}
		cmds = cmds->next;
	}
}

int	exec_builtin(t_cmds *cmds, t_env_var *env_var)
{
	if (cmds->builtin == ECHO)
		return (echo(cmds));
	else if (cmds->builtin == CD)
		return (cd(cmds, env_var));
	else if (cmds->builtin == PWD)
		return (pwd(cmds));
	else if (cmds->builtin == EXPORT)
		return (export(cmds, env_var));
	else if (cmds->builtin == UNSET)
		return (unset(cmds, env_var));
	else if (cmds->builtin == ENV)
		return (env(cmds, env_var));
	else if (cmds->builtin == EXIT)
		return (ft_exit(cmds));
	return (SUCCESS);
}

int	is_directory(t_cmds *cmds)
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

static int	exec_bin(t_cmds *cmds, t_minishell *mini)
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
		return (free(path_cmd), error_fd(1, cmds));
	cmds->fd.pid = fork();
	if (cmds->fd.pid == -1)
		return (free(path_cmd), error_fd(1, cmds));
	if (cmds->fd.pid == 0)
	{
		if (dup_fd(cmds) == ERROR)
			return (free(path_cmd), ft_free_split(env), error_fd(1, cmds));
		if (execve(path_cmd, cmds->args, env) == -1)
			return (free(path_cmd), ft_free_split(env), error_fd(1, cmds));
	}
	free(path_cmd);
	ft_free_split(env);
	return (ret);
}
static int	do_pipe_and_redir(t_cmds *cmds)
{
	int	ret;

	ret = 0;
	if (cmds->next)
	{
		if (handle_pipe(cmds) == ERROR)
			return (ERROR);
	}
	if (cmds->redir)
	{
		if (handle_redir(cmds) == ERROR)
		{
			close_fd(cmds);
			return (ERROR);
		}
	}
	return (ret);
}

static int	exec_cmds(t_cmds *cmds, t_minishell *mini)
{
	int	ret;

	ret = 0;
	if (do_pipe_and_redir(cmds) == ERROR)
		return (ERROR);
	if (cmds->builtin != NO_BUILTIN)
		ret = exec_builtin(cmds, mini->env_var);
	else
		ret = exec_bin(cmds, mini);
	close_fd(cmds);
	return (ret);
}

int	executor(t_minishell *mini)
{
	t_cmds	*tmp;

	tmp = mini->cmds;
	while (tmp)
	{
		tmp->args = expand_args(tmp->args, mini->env_var);
		if (!tmp->args || !tmp->args[0])
		{
			tmp = tmp->next;
			continue ;
		}
		mini->status = exec_cmds(tmp, mini);
		if (!tmp->next)
			wait_child(mini);
		tmp = tmp->next;
	}
	return (SUCCESS);
}