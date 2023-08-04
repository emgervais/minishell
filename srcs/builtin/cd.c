/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/04 10:40:09 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int cd(t_cmds *cmd, t_env_var *env_var)
{
    char	*path;

    if (cmd->argc > 2)
        return (error_fd(cmd->args[0], "too many arguments", 1, cmd));
    set_env_var("OLDPWD", getcwd(NULL, 0), env_var);//protect
    if (cmd->argc == 1)
        path = get_env_var_value("HOME", env_var);
    else
        path = cmd->args[1];
    if (chdir(path) == -1)
    {
        if (cmd->argc == 1)
            return (error_fd(cmd->args[0], "HOME not set", 1, cmd));
        else
            return (error_fd(cmd->args[0], strerror(errno), 1, cmd));
    }
    set_env_var("PWD", getcwd(NULL, 0), env_var);//protect
    return (0);
}