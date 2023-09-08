/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:05 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/07 22:27:53 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_minishell *mini)
{
	int	status;

	mini->waiting_child = 1;
	while (waitpid(-1, &status, 0) != -1)
		if (WIFEXITED(status))
			mini->status = WEXITSTATUS(status);
	mini->waiting_child = 0;
}

void	close_fd(t_cmds *cmds)
{
	if (cmds->fd.fd_in != STDIN_FILENO)
		close(cmds->fd.fd_in);
	if (cmds->fd.fd_out != STDOUT_FILENO)
		close(cmds->fd.fd_out);
}

int	dup_fd(t_cmds *cmds)
{
	if (cmds->fd.fd_in != STDIN_FILENO)
	{
		if (dup2(cmds->fd.fd_in, STDIN_FILENO) == -1)
			return (error_fd(1, cmds, 0));
		close(cmds->fd.fd_in);
	}
	if (cmds->next && cmds->next->fd.fd_in != STDIN_FILENO)
		close(cmds->next->fd.fd_in);
	if (cmds->fd.fd_out != STDOUT_FILENO)
	{
		if (dup2(cmds->fd.fd_out, STDOUT_FILENO) == -1)
			return (error_fd(1, cmds, 0));
		close(cmds->fd.fd_out);
	}
	if (cmds->prev && cmds->prev->fd.fd_out != STDOUT_FILENO)
		close(cmds->prev->fd.fd_out);
	return (SUCCESS);
}

int	handle_pipe(t_cmds *cmds)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (error_fd(1, cmds, 0));
	cmds->fd.fd_out = fd[1];
	cmds->next->fd.fd_in = fd[0];
	return (SUCCESS);
}
