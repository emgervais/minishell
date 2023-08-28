/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:05 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/27 23:31:24 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    dup_fd(t_cmds *cmds)
{
    if (cmds->fd.fd_in != STDIN_FILENO)
    {
        if (dup2(cmds->fd.fd_in, STDIN_FILENO) == -1)
            return (error_fd(1, cmds));
        close(cmds->fd.fd_in);
    }
    if (cmds->fd.fd_out != STDOUT_FILENO)
    {
        if (dup2(cmds->fd.fd_out, STDOUT_FILENO) == -1)
            return (error_fd(1, cmds));
        close(cmds->fd.fd_out);
    }
    return (SUCCESS);
}

int    close_fd(t_cmds *cmds)
{
    if (cmds->fd.fd_in != STDIN_FILENO)
        close(cmds->fd.fd_in);
    if (cmds->fd.fd_out != STDOUT_FILENO)
        close(cmds->fd.fd_out);
    return (SUCCESS);
}

int     handle_redir(t_cmds *cmds)
{
    t_redir *tmp;
    int temp;

    tmp = cmds->redir;
    while (tmp)
    {
        if (tmp->type == HEREDOC)
        {
            temp = handle_heredoc(tmp);
            if (temp == -1)
                return (error_fd(1, cmds));
            if (cmds->fd.fd_in != STDIN_FILENO)
                close(cmds->fd.fd_in);
            cmds->fd.fd_in = temp;
        }
        else if (tmp->type == IN)
        {
            temp = open(tmp->file, O_RDONLY);
            if (temp == -1)
                return (error_fd(1, cmds));
            if (cmds->fd.fd_in != STDIN_FILENO)
                close(cmds->fd.fd_in);
            cmds->fd.fd_in = temp;
        }
        else if (tmp->type == OUT)
        {
            if (cmds->fd.fd_out != STDOUT_FILENO)
                close(cmds->fd.fd_out);
            temp = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (temp == -1)
                return (error_fd(1, cmds));
            cmds->fd.fd_out = temp;
        }
        else if (tmp->type == APPEND)
        {
            if (cmds->fd.fd_out != STDOUT_FILENO)
                close(cmds->fd.fd_out);
            temp = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (temp == -1)
                return (error_fd(1, cmds));
            cmds->fd.fd_out = temp;
        }
        tmp = tmp->next;
    }
    return (SUCCESS);
}

int    handle_pipe(t_cmds *cmds)
{
    int fd[2];

    if (pipe(fd) == -1)
        return (error_fd(1, cmds));
    cmds->fd.fd_out = fd[1];
    cmds->next->fd.fd_in = fd[0];
    return (SUCCESS);
}