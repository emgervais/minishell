/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:05 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 22:38:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    dup_fd(t_cmds *cmds)
{
    if (cmds->fd.fd_in != STDIN_FILENO)
    {
        if (dup2(cmds->fd.fd_in, STDIN_FILENO) == -1)
            return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
        close(cmds->fd.fd_in);
    }
    if (cmds->fd.fd_out != STDOUT_FILENO)
    {
        if (dup2(cmds->fd.fd_out, STDOUT_FILENO) == -1)
            return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
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

int     ft_here_doc(t_cmds *cmds)
{
    int     fd[2];
    char    *line;

    if (pipe(fd) == -1)
        return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
    cmds->fd.fd_in = fd[0];
    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if (ft_strncmp(line, cmds->redir->file, ft_strlen(cmds->redir->file)) == 0)
        {
            free(line);
            break ;
        }
        ft_putendl_fd(line, fd[1]);
        free(line);
    }
    close(fd[1]);
    return (SUCCESS);
}

int     handle_redir(t_cmds *cmds)
{
    t_redir *tmp;

    tmp = cmds->redir;
    while (tmp)
    {
        if (tmp->type == HEREDOC)
        {
            if (ft_here_doc(cmds))
                return (ERROR);
        }
        else if (tmp->type == IN)
        {
            if (cmds->fd.fd_in != STDIN_FILENO)
                close(cmds->fd.fd_in);
            cmds->fd.fd_in = open(tmp->file, O_RDONLY);
            if (cmds->fd.fd_in == -1)
                return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
        }
        else if (tmp->type == OUT)
        {
            if (cmds->fd.fd_out != STDOUT_FILENO)
                close(cmds->fd.fd_out);
            cmds->fd.fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (cmds->fd.fd_out == -1)
                return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
        }
        else if (tmp->type == APPEND)
        {
            if (cmds->fd.fd_out != STDOUT_FILENO)
                close(cmds->fd.fd_out);
            cmds->fd.fd_out = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (cmds->fd.fd_out == -1)
                return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
        }
        tmp = tmp->next;
    }
    return (SUCCESS);
}

int    handle_pipe(t_cmds *cmds)
{
    int fd[2];

    if (pipe(fd) == -1)
        return (error_fd(strerror(errno), NULL, 1, STDERR_FILENO));
    cmds->fd.fd_out = fd[1];
    cmds->next->fd.fd_in = fd[0];
    return (SUCCESS);
}
