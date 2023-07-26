/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:58 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/26 05:01:03 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str, t_cmds *command)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		command->builtin = ECHO;
	else if (ft_strncmp(str, "cd", 3) == 0)
		command->builtin = CD;
	else if (ft_strncmp(str, "pwd", 4) == 0)
		command->builtin = PWD;
	else if (ft_strncmp(str, "export", 7) == 0)
		command->builtin = EXPORT;
	else if (ft_strncmp(str, "unset", 6) == 0)
		command->builtin = UNSET;
	else if (ft_strncmp(str, "env", 4) == 0)
		command->builtin = ENV;
	else if (ft_strncmp(str, "exit", 5) == 0)
		command->builtin = EXIT;
	else
		return (0);
	return (1);
}

static int is_redir(t_cmds *command, char **str, int i)
{
	t_redir			*redir;
	t_redir_type 	type;

	if (ft_strncmp(str[i], ">>", 2) == 0)
		type = DOUBLE_GREAT;
	else if (ft_strncmp(str[i], "<<", 2) == 0)
		type = DOUBLE_LESS;
	else if (ft_strncmp(str[i], ">", 1) == 0)
		type = GREAT;
	else if (ft_strncmp(str[i], "<", 1) == 0)
		type = LESS;
	else
		return (0);
	if (init_redir(&redir, type, str[i + 1]))
		return (1);
	if (add_redir(&command, redir))
		return (1);
	return (0);
}

static t_cmds *parse_arg(t_cmds **commands, t_cmds *command, char **str, int i)
{
	t_cmds	*new_command;

	if (is_redir(command, str, i))
		return (command);
	if (str[i][0] == '|' && str[i][1] == '\0')
	{
		if (add_command(commands, command))
			return (NULL);
		new_command = init_command();
		if (!new_command)
			return (NULL);
		return (new_command);
	}
	if (command->argc == 0 && is_builtin(str[i], command))
		return (command);
	if (add_arg(&command, str[i]))
		return (NULL);
	return (command);
}

static int	parse_commands(char **str, t_cmds **commands)
{
	t_cmds	*command;
	int		i;

	command = init_command();
	if (!command)
		return (ERROR);
	i = 0;
	while (str[i])
	{
		command = parse_arg(commands, command, str, i);
		if (!command)
			return (ERROR);
		i++;
	}
	if (add_command(commands, command))
		return (ERROR);
	return (SUCCESS);
}

t_cmds	*init_commands(char **str)
{
	t_cmds	*commands;

	commands = NULL;
	if (parse_commands(str, &commands))
		return (NULL);
	return (commands);
}