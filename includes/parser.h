/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:01:18 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/18 16:36:36 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"


/*
** Structure for commands
**
** args: array of arguments
** argc: number of arguments
** pipe: 1 if pipe is present, 0 otherwise
** redir: 1 if redirection is present, 0 otherwise
** redir_type: 0 if no redirection, 1 if <, 2 if >, 3 if >>, 4 if <<
** redir_file: file to redirect to
** next: pointer to next command
** prev: pointer to previous command
*/
typedef struct s_cmds
{
	char			**args;
	int				argc;
	int				pipe;
	int				redir;
	int				redir_type;
	char			*redir_file;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

// free
void	free_command(t_cmds *command);
void	free_commands(t_cmds *commands);

// init
int		parse_commands(char **str, t_cmds **commands);
t_cmds	*init_commands(char **str);

void	check_double_quotes(t_cmds *commands);
void	replace_env_var(t_cmds *commands);

void	parser(char **str);

#endif