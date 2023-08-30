/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:05 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/30 00:58:45 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_fd(t_cmds *cmds)
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

int	close_fd(t_cmds *cmds)
{
	if (cmds->fd.fd_in != STDIN_FILENO)
		close(cmds->fd.fd_in);
	if (cmds->fd.fd_out != STDOUT_FILENO)
		close(cmds->fd.fd_out);
	return (SUCCESS);
}

int	no_heredoc(t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	handle_pipe(t_cmds *cmds)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (error_fd(1, cmds));
	cmds->fd.fd_out = fd[1];
	cmds->next->fd.fd_in = fd[0];
	return (SUCCESS);
}
