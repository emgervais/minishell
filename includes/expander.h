/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:13:14 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/05 00:09:15 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int			is_valid_key(char *key);
int			set_env_var(char *key, char *value, t_env_var *env_var);
int			env_var_len(t_env_var *env_var);
char		*get_env_var_value(char *key, t_env_var *env_var);
char		*expand_arg(char *arg, t_env_var *env_var, char **keys);
char		**expand_args(char **args, t_env_var *env_var);
t_env_var	*new_env_var(char *key_value);
int			add_env_var(t_env_var *env_var, char *key_value);
t_env_var	*init_env_var(char **envp);
char		**get_keys(char *arg, int i, int j);
char		*skip_quotes(char *arg, int *i);
char		*remove_quotes_arg(char *args, char *new_arg);
char		**remove_quotes(char **args);
int			remove_quotes_redir(t_redir *redir);

#endif