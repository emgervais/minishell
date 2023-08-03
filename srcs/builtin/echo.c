/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:21:34 by egervais          #+#    #+#             */
/*   Updated: 2023/08/02 22:58:42 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		echo(t_cmds *cmds)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (cmds->argc > 1)
    {
        if (ft_strncmp(cmds->args[1], "-n", 3) == 0)
        {
            n = 1;
            i++;
        }
        while (i < cmds->argc)
        {
            ft_putstr_fd(cmds->args[i], cmds->fd.fd_out);
            if (i + 1 < cmds->argc)
                ft_putchar_fd(' ', cmds->fd.fd_out);
            i++;
        }
    }
    if (!n)
        ft_putchar_fd('\n', cmds->fd.fd_out);
    return (SUCCESS);
}