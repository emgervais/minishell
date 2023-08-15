/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:31:34 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/15 13:48:06 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(t_cmds *cmd)
{
    char *cwd;

    cwd = malloc(sizeof(char) * 1025);
    if (!cwd)
        return (ERROR);
    getcwd(cwd, sizeof(char) * 1025);
    if (!cwd)
        return (error_fd(cmd->args[0], strerror(errno), 1, cmd));
    ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
    return (SUCCESS);
}