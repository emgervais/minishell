/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:42:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/26 05:35:10 by ele-sage         ###   ########.fr       */
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

#endif