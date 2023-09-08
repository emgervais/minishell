/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:03:22 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/07 22:32:49 by ele-sage         ###   ########.fr       */
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
# include <termios.h>
# include <sys/ioctl.h>
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

t_minishell	*minishell(void);
void		lsh_loop(t_minishell *mini);

#endif