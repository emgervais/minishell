/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/30 01:01:04 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_pid(t_cmds *cmds)
{
	int	status;

	status = 0;
	waitpid(cmds->fd.pid, &status, 0);
	if (WIFEXITED(status)) // return the exit status of the child
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		// return the signal that caused the child process to terminate
		return (WTERMSIG(status) + 128);
	return (SUCCESS);
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

static int	exec_bin(t_cmds *cmds, t_env_var *env_var)
{
	char	*path_cmd;
	char	**env;
	int		ret;

	ret = 0;
	path_cmd = get_path(cmds->args[0], env_var, cmds);
	if (!path_cmd)
		return (cmds->fd.status);
	env = env_var_to_array(env_var);
	if (!env)
		return (free(path_cmd), error_fd(1, cmds));
	cmds->fd.pid = fork();
	if (cmds->fd.pid == 0)
	{
		ret = dup_fd(cmds);
		if (ret == SUCCESS)
			ret = execve(path_cmd, cmds->args, env);
	}
	else if (cmds->fd.pid < 0)
		ret = error_fd(1, cmds);
	return (ft_free_split(env), free(path_cmd), ret);
}

int	exec_cmds(t_cmds *cmds, t_env_var *env_var)
{
	int	ret;

	if (cmds->next)
		if (handle_pipe(cmds) == ERROR)
			return (ERROR);
	if (cmds->redir)
	{
		if (handle_redir(cmds) == ERROR)
		{
			if (cmds->next)
				close(cmds->fd.fd_out);
			return (ERROR);
		}
	}
	if (cmds->builtin != NO_BUILTIN)
		ret = exec_builtin(cmds, env_var);
	else
	{
		ret = exec_bin(cmds, env_var);
		if (cmds->next)
			close(cmds->fd.fd_out);
	}
	close_fd(cmds);
	return (ret);
}

int	executor(t_minishell *mini)
{
	t_cmds *tmp;
	char **args;

	tmp = mini->cmds;
	while (tmp)
	{
		if (tmp->argc != 0)
		{
			args = expand_args(tmp->args, mini->env_var);
			if (!args)
			{
				tmp = tmp->next;
				mini->status = 1;
				continue ;
			}
			tmp->args = args;
			if (tmp->args && tmp->args[0] && tmp->args[0][0])
				mini->status = exec_cmds(tmp, mini->env_var);
		}
		if (!tmp->next && tmp->builtin == NO_BUILTIN && !mini->status
			&& tmp->args && tmp->args[0] && tmp->args[0][0])
			mini->status = wait_pid(tmp);
		tmp = tmp->next;
	}
	return (mini->status);
}