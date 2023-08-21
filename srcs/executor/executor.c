/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/21 16:45:32 by ele-sage         ###   ########.fr       */
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
    else if (cmds->builtin == EXIT)
        return (ft_exit(cmds));
    return (SUCCESS);
}
//returns NULL if failing
static char *get_path(char *cmd, t_env_var *env_var)
{
    char    **path;
    char    *path_cmd;
    int     i;

    path = ft_split(get_env_var_value("PATH", env_var), ':');
    i = 0;
    while (path && path[i])
    {
        path[i] = ft_strjoin(path[i], "/");
        path[i] = ft_strjoinfree(path[i], cmd, 1);
        if (path[i] && access(path[i], F_OK) == 0)
        {
            path_cmd = ft_strdup(path[i]);
            break ;
        }
        i++;
    }
    if (!path || !path[i])
        path_cmd = NULL;
    ft_free_split(path);
    return (path_cmd);
}
//returns null if failing
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
        env[i] = ft_strjoin(env_var->key, "=");
        env[i] = ft_strjoinfree(env[i], env_var->value, 1);
        if(!env[i])
            return(ft_free_split(env), NULL);
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
            return (error_fd(cmds->args[0], strerror(errno), 127, cmds));//free env
    }
    else if (cmds->fd.pid < 0)
        return (error_fd(cmds->args[0], strerror(errno), 1, cmds)); //free env
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
    return (ret);
}

int executor(t_cmds *cmds, t_env_var *env_var)
{
    t_cmds	*tmp;
    int		ret;

    tmp = cmds;
    ret = 0;
    while (tmp)
    {
        if (tmp->argc != 0)
        {
            tmp->args = expand_args(tmp->args, env_var);
            if (!tmp->args)
                return (ERROR);
            ret = exec_cmds(tmp, env_var);
        }
        tmp = tmp->next;
    }
    cmds->e_status = ret;
    return (ret);
}
