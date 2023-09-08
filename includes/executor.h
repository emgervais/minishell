/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:26:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/07 20:26:11 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		executor(t_minishell *mini);
int		exec_bin(t_cmds *cmds, t_minishell *mini);

void	wait_child(t_minishell *mini);
int		dup_fd(t_cmds *cmds);
void	close_fd(t_cmds *cmds);
int		no_heredoc(t_cmds *cmds);
int		handle_redir(t_cmds *cmds, t_minishell *mini);
int		handle_pipe(t_cmds *cmds);
int		handle_heredoc(t_redir *redir, t_minishell *mini);

#endif