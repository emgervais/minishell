/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:25:23 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/08 19:56:38 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_heredoc(t_redir *tmp, t_redir **tmp_error, t_cmds *cmds,
					t_minishell *mini)
{
	int	new_fd;

	new_fd = handle_heredoc(tmp, mini);
	if (new_fd == -1)
		return (error_fd(1, cmds, 1));
	if (cmds->fd.fd_in != STDIN_FILENO)
		close(cmds->fd.fd_in);
	cmds->fd.fd_in = new_fd;
	if (*tmp_error)
		close(new_fd);
	return (SUCCESS);
}

static int	redir_in(t_redir *tmp, t_redir **tmp_error, t_cmds *cmds)
{
	int	new_fd;

	new_fd = open(tmp->file, O_RDONLY);
	if (new_fd == -1 && no_heredoc(cmds))
		return (error_fd(1, cmds, 1));
	else if (new_fd == -1 && !*tmp_error)
		*tmp_error = tmp;
	else if (new_fd != -1 && !*tmp_error)
	{
		if (cmds->fd.fd_in != STDIN_FILENO)
			close(cmds->fd.fd_in);
		cmds->fd.fd_in = new_fd;
	}
	else if (new_fd != -1 && *tmp_error)
		close(new_fd);
	return (SUCCESS);
}

static int	redir_out(t_redir *tmp, t_cmds *cmds)
{
	int	new_fd;

	if (cmds->fd.fd_out != STDOUT_FILENO)
		close(cmds->fd.fd_out);
	if (tmp->type == OUT)
		new_fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == APPEND)
		new_fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (SUCCESS);
	if (new_fd == -1)
		return (error_fd(1, cmds, 1));
	cmds->fd.fd_out = new_fd;
	return (SUCCESS);
}

static int	redir_loop(t_redir *tmp, t_redir **tmp_error, t_cmds *cmds,
				t_minishell *mini)
{
	if (tmp->type == HEREDOC)
		return (redir_heredoc(tmp, tmp_error, cmds, mini));
	else if (tmp->type == IN)
		return (redir_in(tmp, tmp_error, cmds));
	else if (tmp->type == OUT || tmp->type == APPEND)
		return (redir_out(tmp, cmds));
	return (SUCCESS);
}

int	handle_redir(t_cmds *cmds, t_minishell *mini)
{
	t_redir	*tmp;
	t_redir	*tmp_error;

	tmp = cmds->redir;
	tmp_error = NULL;
	while (tmp)
	{
		if (redir_loop(tmp, &tmp_error, cmds, mini) != SUCCESS)
			return (ERROR);
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
