/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:10:06 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/28 21:21:42 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int    error_fd(int status, t_cmds *cmds)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmds->args[0], STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(strerror(errno), STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    if (cmds)
        cmds->fd.status = status;
    return (status);
}

int    error_denied(t_cmds *cmds, char **path)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmds->args[0], STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("Permission denied", STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    cmds->fd.status = 126;
    ft_free_split(path);
    return (126);
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

int    syntax_error_lexer(char token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
    ft_putchar_fd(token, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    minishell()->status = 258;
    return (0);
}