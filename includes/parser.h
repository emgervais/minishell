/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:01:18 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/21 17:05:37 by ele-sage         ###   ########.fr       */
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
	int				(*builtin)(struct s_cmds *cmd, t_env_var **env_var);
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

// init utils
t_cmds	*init_command(void);
int 	add_arg(t_cmds **command, char *arg);
int		add_command(t_cmds **commands, t_cmds *command);
int		init_redir(t_redir **redir, t_redir_type type, char *file);
int		add_redir(t_cmds **command, t_redir *redir);

// init
t_cmds	*parser(char **str);
t_cmds	*init_commands(char **str);


// init env vars
int 	replace_env_vars(char **str, t_env_var *env_var);
int 	init_env_var_list(char **str, t_env_var **env_var);
void	check_double_quotes(char **str);

#endif