/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:10:06 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 18:36:15 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	error_fd_redir(int status, t_cmds *cmds)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmds->redir->file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (cmds)
		cmds->fd.status = status;
	return (status);
}

int	error_fd(int status, t_cmds *cmds)
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

void	*error_path(t_cmds *cmds, char *path, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	cmds->fd.status = 127;
	if (strncmp(error, "Permission denied", 17) == 0)
	{
		cmds->fd.status = 126;
		free(path);
	}
	return (NULL);
}

int	syntax_error(char token)
{
	if (token != '|')
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
	minishell()->status = 258;
	return (0);
}

int	syntax_error_lexer(char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	minishell()->status = 258;
	return (0);
}
