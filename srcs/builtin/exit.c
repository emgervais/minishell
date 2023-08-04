/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:40:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 09:02:46 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int	ft_exit(t_cmds *cmd, t_env_var *env_var)
{
    int    i;
    int    ret;

    i = 0;
    ret = 0;
    if (cmd->argc == 1)
    {
        cmd->fd.status = 0;
        return (SUCCESS);
    }
    if (cmd->argc > 2)
        return (error_fd(cmd->args[0], "too many arguments", 1, cmd));

    while (cmd->args[1][i])
    {
        if (!ft_isdigit(cmd->args[1][i]))
            return (error_fd(cmd->args[0], "numeric argument required", 255, cmd));
        i++;
    }
    if (cmd->args[1][i] == '-')
        return (error_fd(cmd->args[0], "numeric argument required", 255, cmd));
    ret = ft_atoi(cmd->args[1]);
}
