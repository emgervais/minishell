/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:22:47 by egervais          #+#    #+#             */
/*   Updated: 2023/09/01 18:59:25 by egervais         ###   ########.fr       */
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

# define MAX_EXIT_CODE "9223372036854775807"

char	*add_one_char(char *s1, char c, int malloced);

int		env(t_cmds *cmd, t_env_var *env_var);
int		echo(t_cmds *cmd);
int		cd(t_cmds *cmd, t_env_var *env_var);
int		unset(t_cmds *cmd, t_env_var *env_var);
void	delete_env_var(char *key, t_env_var *env_var);
int		export(t_cmds *cmd, t_env_var *env_var);
int		pwd(t_cmds *cmd);
int		ft_exit(t_cmds *cmd);

#endif