/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:01:18 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/20 22:23:13 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_redir_type
{
	NO_REDIR,
	LESS,
	GREAT,
	DOUBLE_LESS,
	DOUBLE_GREAT
}	t_redir_type;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmds
{
	char			**args;
	int				argc;
	t_redir			*redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

// free
void	free_command(t_cmds *command);
void	free_commands(t_cmds *commands);
void    free_all_env_vars(t_env_var *env_var);

// init
int		parse_commands(char **str, t_cmds **commands);
t_cmds	*init_commands(char **str);
t_env_var    *init_env_var_list(char **str);

void	check_double_quotes(t_cmds *commands);

void	parser(char **str);

#endif