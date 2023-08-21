/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/21 16:57:03 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int cd(t_cmds *cmd, t_env_var *env_var)
{
    char	*path;

    if (cmd->argc > 2)
        return (error_fd(cmd->args[0], "too many arguments", 1, cmd));
    if(set_env_var("OLDPWD", getcwd(NULL, 0), env_var))
        return(ERROR);
    if (cmd->argc == 1)
        path = get_env_var_value("HOME", env_var);
    else
        path = cmd->args[1];
    if (chdir(path) == -1)
    {
        if (cmd->argc == 1)
            return (error_fd(cmd->args[0], "HOME not set", 1, cmd));
        else
            return (error_fd(cmd->args[0], "No such file or directory", 1, cmd));
    }
    if(set_env_var("PWD", getcwd(NULL, 0), env_var))
        return(ERROR);
    cmd->e_status = 0;
    return (0);
}