/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/01 16:27:14 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

    // if (cmd->argc == 0 && cmd->builtin == NO_BUILTIN)
    //     return (ERROR);
    // if (cmd->builtin == ECHO)
    //     return (echo());
    // else if (cmd->builtin == CD)
    //     return (cd());
    // else if (cmd->builtin == PWD)
    //     return (pwd());
    // else if (cmd->builtin == EXPORT)
    //     return (export());
    // else if (cmd->builtin == UNSET)
    //     return (unset());
    // else if (cmd->builtin == ENV)
    //     return (env());
    // else if (cmd->builtin == EXIT)
    //     return (exit());
    // else
    //     return (ft_execve(cmd, env_var));
 static int	exec_cmds(t_cmds *cmd, t_env_var *env_var, int *end)
 {
    t_redir *temp;
    int in = 0;
    int out = 0;

    temp = cmd->redir;
    while(temp)
    {
        if(temp->file == 2 || temp->file == 4)
        {
            if(out)
                close(out);
            if(temp->file == 2)
                out = open(temp->file, O_TRUNC | O_CREAT | O_RDWR, 0000644);
            else
                out = open(temp->file, O_APPEND | O_CREAT | O_RDWR, 0000644);
            if (out < 0)
                return (1);
        }
        else if (temp->file == 1)
        {
            if (in)
                close (in);
            in = open(temp->file, O_RDONLY);
            if (in < 0)
                return (1);
        }
        else if (temp->file == 3)
        {
            //heredoc
        }
    }
 }
int		executor(t_cmds *cmds, t_env_var *env_var)
{
    t_cmds	*tmp;
    int		ret;
    int end[2];
    pid_t pid;

    tmp = cmds;
    if(pipe(end) == -1)
        return (-1);
    while (tmp)
    {
        tmp->args = expand_args(tmp->args, env_var);
        if(!tmp->args)
            return (-1);
        pid = fork();
        if(!pid)
        {
            ret = exec_cmds(tmp, env_var, end);
            if (ret == ERROR)
                return (ERROR);
        }
        tmp = tmp->next;
    }
    return (ERROR);
}