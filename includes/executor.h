/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:26:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/31 20:05:08 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		executor(t_minishell *mini);

int     dup_fd(t_cmds *cmds);
void    close_fd(t_cmds *cmds);
int     no_heredoc(t_cmds *cmds);
int		handle_redir(t_cmds *cmds);
int		handle_pipe(t_cmds *cmds);
int     handle_heredoc(t_redir *redir);


#endif