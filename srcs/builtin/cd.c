/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/04 08:37:29 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int cd(t_cmds *cmd, t_env_var *env_var)
{
    char	*path;
    char	*oldpwd;

    if (cmd->argc > 2)
        return (error_fd(cmd->args[0], "too many arguments", 1, cmd));
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
    oldpwd = malloc(sizeof(char) * 1025);
    if (!oldpwd)
        return (ERROR);
    getcwd(oldpwd, sizeof(char) * 1025);
    set_env_var("OLDPWD", oldpwd, env_var);
    set_env_var("PWD", getcwd(NULL, 0), env_var);
    free(oldpwd);
    return (0);
}