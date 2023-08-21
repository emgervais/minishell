/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:10:06 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/21 19:04:13 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int    error_fd(char *str, char *err, int status, t_cmds *cmds)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    if (err)
    {
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd(err, STDERR_FILENO);
    }
    ft_putstr_fd("\n", STDERR_FILENO);
    if (cmds)
        cmds->fd.status = status;
    return (status);
}

int    syntax_error(char token)
{
    if (token != '|')
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
    else
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
    minishell()->status = 258;
    return (0);
}