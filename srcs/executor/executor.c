/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 10:30:20 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    exec_builtin(t_cmds *cmds, t_env_var *env_var)
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
    return (SUCCESS);
}

static char *get_path(char *cmd, t_env_var *env_var)
{
    char    **path;
    char    *path_cmd;
    int     i;

    path = ft_split(get_env_var_value("PATH", env_var), ':');
    i = 0;
    while (path && path[i])
    {
        path[i] = ft_strjoin(path[i], "/");//leaks + protect
        path[i] = ft_strjoin(path[i], cmd);
        if (access(path[i], F_OK) == 0)
        {
            path_cmd = ft_strdup(path[i]);//protect
            break ;
        }
        i++;
    }
    if (!path || !path[i])
        path_cmd = NULL;
    ft_free_split(path);
    return (path_cmd);//makesure protected when calling
}

static char **env_var_to_array(t_env_var *env_var)
{
    char    **env;
    int     i;

    env = (char **)malloc(sizeof(char *) * (env_var_len(env_var) + 1));
    if (!env)
        return (NULL);
    i = 0;
    while (env_var)
    {
        env[i] = ft_strjoin(env_var->key, "=");//leaks + protect
        env[i] = ft_strjoin(env[i], env_var->value);
        env_var = env_var->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}

static int  exec_bin(t_cmds *cmds, t_env_var *env_var)
{
    char    *path_cmd;
    char    **env;

    path_cmd = get_path(cmds->args[0], env_var);
    if (!path_cmd)
        return (error_fd(cmds->args[0], "command not found", 127, cmds));
    env = env_var_to_array(env_var);
    if (!env)
        return (ERROR);
    cmds->fd.pid = fork();
    if (cmds->fd.pid == 0)
    {
        if (dup_fd(cmds) == ERROR)
            return (ERROR);
        if (execve(path_cmd, cmds->args, env) == -1)
            return (error_fd(cmds->args[0], strerror(errno), 127, cmds));
    }
    else if (cmds->fd.pid < 0)
        return (error_fd(cmds->args[0], strerror(errno), 1, cmds));
    else
    {
        waitpid(cmds->fd.pid, &cmds->fd.status, 0);
        if (WIFEXITED(cmds->fd.status))
            cmds->fd.status = WEXITSTATUS(cmds->fd.status);
    }
    ft_free_split(env);
    free(path_cmd);
    return (SUCCESS);
}

int    exec_cmds(t_cmds *cmds, t_env_var *env_var)
{
    int     ret;

    if (cmds->next)
    {
        if (handle_pipe(cmds) == ERROR)
            return (ERROR);
    }
    if (cmds->redir)
    {
        if (handle_redir(cmds) == ERROR)
            return (ERROR);
    }
    if (cmds->builtin != NO_BUILTIN)
        ret = exec_builtin(cmds, env_var);
    else
        ret = exec_bin(cmds, env_var);
    if (close_fd(cmds) == ERROR)
        return (ERROR);
    return (ret); //orm ake sure its protected when called
}

int executor(t_cmds *cmds, t_env_var *env_var)
{
    t_cmds	*tmp;
    int		ret;

    tmp = cmds;
    while (tmp)
    {
        if (tmp->argc != 0)
        {
            tmp->args = expand_args(tmp->args, env_var);
            if (!tmp->args)
                return (ERROR);
            ret = exec_cmds(tmp, env_var);
            if (ret == ERROR)
                return (ERROR);       
        }
        tmp = tmp->next;
    }
    return (SUCCESS);
}
