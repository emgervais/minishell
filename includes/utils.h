/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:42:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 05:55:36 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// free
void	free_command(t_cmds *command);
void	free_commands(t_cmds *commands);
void    free_env_vars(t_env_var *env_var);

// unix signals
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	init_signals(void);
void	reset_signals(void);

// print utils
void	print_env_var(t_env_var *env_var);
void	print_commands(t_cmds *commands);

// error utils
int     error_fd(char *str, char *err, int status, t_cmds *cmds);

#endif