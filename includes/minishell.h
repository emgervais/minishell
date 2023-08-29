/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:03:22 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/29 13:28:19 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/include/libft.h"

# include "builtin.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "utils.h"


# define ERROR 1
# define SUCCESS 0

# define TRUE 1
# define FALSE 0

typedef struct s_minishell
{
    t_env_var   *env_var;
    t_cmds      *cmds;
    int         status;
}               t_minishell;

t_minishell *minishell(void);
int        lsh_loop(char **envp);

# endif