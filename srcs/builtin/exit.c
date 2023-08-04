/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:40:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 11:20:54 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	in_range(char *str)
{
    int	i;

    i = 0;
    if (ft_strlen(str) > ft_strlen(MAX_EXIT_CODE))
        return (0);
    if (ft_strlen(str) < ft_strlen(MAX_EXIT_CODE))
        return (1);
    while (str[i++])
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            if (str[i] > MAX_EXIT_CODE[i])
                return (0);
            else if (str[i] < MAX_EXIT_CODE[i])
                return (1);
        }
        else
            return (0);
    }
    return (1);
}

int	ft_exit(t_cmds *cmd)
{
    int	i;

    i = 0;
    ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (cmd->argc > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (1);
    }
    if (cmd->argc == 2)
    {
        if (!in_range(cmd->args[1]))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(cmd->args[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            return (2);
        }
        i = ft_atoi(cmd->args[1]);
    }
    free_all(minishell());
    exit(i);
}
