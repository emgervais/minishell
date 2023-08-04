/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:13:14 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 08:26:05 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

int     	is_valid_key(char *key);
int         set_env_var(char *key, char *value, t_env_var *env_var);
int         env_var_len(t_env_var *env_var);
char	    *get_env_var_value(char *key, t_env_var *env_var);
char	    **expand_args(char **args, t_env_var *env_var);
t_cmds      *expander(t_cmds *cmds, t_env_var *env_var);
t_env_var	*new_env_var(char *key_value);
int         add_env_var(t_env_var *env_var, char *key_value);
t_env_var	*init_env_var(char **envp);


#endif