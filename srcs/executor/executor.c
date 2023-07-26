/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/26 04:55:57 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	exec_cmds(t_cmds *cmd, t_env_var *env_var)
// {
//     if (cmd->argc == 0 && cmd->builtin == NO_BUILTIN)
//         return (ERROR);
//     if (cmd->builtin == ECHO)
//         return (echo());
//     else if (cmd->builtin == CD)
//         return (cd());
//     else if (cmd->builtin == PWD)
//         return (pwd());
//     else if (cmd->builtin == EXPORT)
//         return (export());
//     else if (cmd->builtin == UNSET)
//         return (unset());
//     else if (cmd->builtin == ENV)
//         return (env());
//     else if (cmd->builtin == EXIT)
//         return (exit());
//     else
//         return (ft_execve(cmd, env_var));
// }


int		executor(t_cmds *cmds, t_env_var *env_var)
{
    (void)cmds;
    (void)env_var;
    // t_cmds	*tmp;
    // int		ret;

    // tmp = cmds;
    // while (tmp)
    // {
    //     ret = exec_cmds(tmp, env_var);
    //     if (ret == ERROR)
    //         return (ERROR);
    //     tmp = tmp->next;
    // }
    return (ERROR);
}