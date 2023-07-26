/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:01:18 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/26 02:24:38 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "builtin.h"

typedef enum e_builtin
{
	NO_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef enum e_redir_type
{
	NO_REDIR,
	LESS,
	GREAT,
	DOUBLE_LESS,
	DOUBLE_GREAT
}	t_redir_type;

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
	t_builtin		builtin;
	t_redir			*redir;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

// init commands utils
t_cmds	*init_command();
int 	add_arg(t_cmds **command, char *arg);
int		add_command(t_cmds **commands, t_cmds *command);
int		init_redir(t_redir **redir, t_redir_type type, char *file);
int		add_redir(t_cmds **command, t_redir *redir);

// init commands
t_cmds	*parser(char **str);
t_cmds	*init_commands(char **str);


#endif