/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:22:47 by egervais          #+#    #+#             */
/*   Updated: 2023/08/02 20:46:30 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parser.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

char    *add_one_char(char *s1, char c, int malloced);
int     open_file(t_cmds *cmds);

int     env(t_env_var *list, int ac);
int     echo(t_cmds *cmds);
int     cd(char **args, int ac, t_env_var *var);
int     unset(t_env_var *env, char **var);
int     export(char **args, t_env_var *list);
int     pwd(int ac);

#endif