/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:13:14 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 15:03:30 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef EXPANDER_H
# define EXPANDER_H

char	    *get_env_var_value(char *key, t_env_var *env_var);
char	    **expand_args(char **args, t_env_var *env_var);
t_cmds      *expander(t_cmds *cmds, t_env_var *env_var);
t_env_var   *new_env_var(char *key, char *value);
int         add_env_var(t_env_var *env_var, char *envp);
t_env_var	*init_env_var(char **envp);
int         env_var_len(t_env_var *env_var);

#endif