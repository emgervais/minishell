/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:42:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/23 11:51:51 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;

// free
void	free_command(t_cmds *command);
void	free_commands(t_cmds *commands);
void    free_env_vars(t_env_var *env_var);
void	free_all(t_minishell *mini);

// unix signals
void	init_signals(void);
void	reset_signals(void);

// print utils
void	print_env_var(t_env_var *env_var);
void	print_commands(t_cmds *commands);

// error utils
int     error_fd(char *err, int status, t_cmds *cmds);
int     syntax_error(char token);
int     syntax_error_lexer(char token);

//string utils
char	*ft_strjoinfree(const char *s1, const char *s2, int malloced);
char	*ft_substrfree(char const *s, unsigned int start, size_t len, int malloced);

#endif