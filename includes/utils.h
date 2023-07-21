/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:42:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/21 13:52:55 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// free
void	free_command(t_cmds *command);
void	free_commands(t_cmds *commands);
void    free_env_vars(t_env_var *env_var);
void	free_all(t_cmds *commands, t_env_var *env_var, char **str);

// unix signals
// void	sigint_handler(int sig);
// void	sigquit_handler(int sig);
// void	init_signals(void);
// void	reset_signals(void);

// error

#endif