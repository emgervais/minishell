/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:05 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/29 18:24:51 by egervais         ###   ########.fr       */
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

int no_heredoc(t_cmds *cmds)
{
    t_redir *tmp;

    tmp = cmds->redir;

    while(tmp)
    {
        if(tmp->type == HEREDOC)
            return(0);
        tmp = tmp->next;
    }
    return (1);
}

int     handle_redir(t_cmds *cmds)
{
    t_redir *tmp;
    t_redir *tmp_error;
    int temp;

    tmp = cmds->redir;
    tmp_error = NULL;
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
            if(tmp_error)
                close(temp);
        }
        else if (tmp->type == IN)
        {
            temp = open(tmp->file, O_RDONLY);
            if (temp == -1 && no_heredoc(cmds))
                return (error_fd(1, cmds));
            else if (temp == -1 && !tmp_error)
                tmp_error = tmp;
            else if (temp != -1 && !tmp_error)
            {
                if (cmds->fd.fd_in != STDIN_FILENO)
                    close(cmds->fd.fd_in);
                cmds->fd.fd_in = temp;
            }
            else if(temp != -1 && tmp_error)
                close(temp);//
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
    if (tmp_error)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(tmp_error->file, STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        return (1);
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
