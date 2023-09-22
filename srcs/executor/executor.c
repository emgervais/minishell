/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/22 12:46:47 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmds *cmds, t_env_var *env_var)
{
	if (cmds->builtin == _ECHO)
		return (echo(cmds));
	else if (cmds->builtin == _CD)
		return (cd(cmds, env_var));
	else if (cmds->builtin == _PWD)
		return (pwd(cmds));
	else if (cmds->builtin == _EXPORT)
		return (export(cmds, env_var));
	else if (cmds->builtin == _UNSET)
		return (unset(cmds, env_var));
	else if (cmds->builtin == _ENV)
		return (env(cmds, env_var));
	else if (cmds->builtin == _EXIT)
		return (ft_exit(cmds));
	return (SUCCESS);
}

static int	exec_cmds(t_cmds *cmds, t_minishell *mini)
{
	int	ret;

	ret = SUCCESS;
	if (cmds->next)
		if (handle_pipe(cmds) == ERROR)
			ret = ERROR;
	if (cmds->redir && ret == SUCCESS)
		if (handle_redir(cmds, mini) == ERROR)
			ret = ERROR;
	if (ret == SUCCESS)
	{
		if (cmds->builtin)
			ret = exec_builtin(cmds, mini->env_var);
		else if (cmds->args && cmds->args[0])
			ret = exec_bin(cmds, mini);
	}
	close_fd(cmds);
	return (ret);
}

int	adjust_ac(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	executor(t_minishell *mini)
{
	t_cmds	*tmp;

	tmp = mini->cmds;
	while (tmp)
	{
		if (tmp->argc)
			tmp->args = expand_args(tmp->args, mini->env_var);
		if ((!tmp->args || !tmp->args[0]) && !tmp->redir)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->argc)
			tmp->argc = adjust_ac(tmp->args);
		mini->status = exec_cmds(tmp, mini);
		if (!tmp->next)
			wait_child(mini);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
