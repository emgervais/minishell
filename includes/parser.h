/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:01:18 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/08 19:54:46 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "builtin.h"
# include "minishell.h"

typedef enum e_builtin
{
	NO_BUILTIN,
	_ECHO,
	_CD,
	_PWD,
	_EXPORT,
	_UNSET,
	_ENV,
	_EXIT
}						t_builtin;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef enum e_redir_type
{
	NO_REDIR,
	IN,
	OUT,
	APPEND,
	HEREDOC
}						t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_fd
{
	int					fd_in;
	int					fd_out;
	int					pid;
	int					status;
}						t_fd;

typedef struct s_cmds
{
	t_fd				fd;
	char				**args;
	int					argc;
	t_builtin			builtin;
	t_redir				*redir;
	struct s_cmds		*next;
	struct s_cmds		*prev;
}						t_cmds;

typedef struct s_minishell
{
	t_env_var			*env_var;
	t_cmds				*cmds;
	int					status;
	int					waiting_child;
	int					ctrl_c;
	int					heredoc;
}						t_minishell;

// init commands utils
t_cmds	*init_command(void);
int		add_arg(t_cmds **command, char *arg);
int		add_command(t_cmds **commands, t_cmds *command);
int		add_redir(t_cmds **command, t_redir *redir);
int		init_redir(t_redir **redir, t_redir_type type, char *file);
// init commands
int		parser(char **str, t_minishell *mini);

#endif