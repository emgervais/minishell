/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:26:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/29 04:53:36 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		executor(t_cmds *cmds, t_env_var *env_var);

int     dup_fd(t_cmds *cmds);
int     close_fd(t_cmds *cmds);
int		handle_redir(t_cmds *cmds);
int		handle_pipe(t_cmds *cmds);
int     exec_cmds(t_cmds *cmds, t_env_var *env_var);
int     handle_heredoc(t_redir *redir);

#endif