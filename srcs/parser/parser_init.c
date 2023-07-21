/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:58 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/20 22:29:37 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmds	*init_command(void)
{
	t_cmds	*command;

	command = (t_cmds *)malloc(sizeof(t_cmds));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->argc = 0;
	command->redir = NULL;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

static int add_arg(t_cmds **command, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * ((*command)->argc + 2));
	if (!tmp)
		return (ERROR);
	while (i < (*command)->argc)
	{
		tmp[i] = (*command)->args[i];
		i++;
	}
	tmp[i] = ft_strdup(arg);
	tmp[i + 1] = NULL;
	if ((*command)->args)
		free((*command)->args);
	(*command)->args = tmp;
	(*command)->argc++;
	return (SUCCESS);
}

static int	add_command(t_cmds **commands, t_cmds *command)
{
	t_cmds	*tmp;

	if (!commands || !command)
		return (ERROR);
	if (!*commands)
	{
		*commands = command;
		return (SUCCESS);
	}
	tmp = *commands;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = command;
	command->prev = tmp;
	return (SUCCESS);
}

static int	init_redir(t_redir **redir, t_redir_type type, char *file)
{
	*redir = (t_redir *)malloc(sizeof(t_redir));
	if (!*redir)
		return (ERROR);
	(*redir)->type = type;
	(*redir)->file = ft_strdup(file);
	(*redir)->next = NULL;
	return (SUCCESS);
}

static int	add_redir(t_cmds **command, t_redir *redir)
{
	t_redir	*tmp;

	if (!command || !redir)
		return (ERROR);
	if (!(*command)->redir)
	{
		(*command)->redir = redir;
		return (SUCCESS);
	}
	tmp = (*command)->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
	return (SUCCESS);
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

	if (ft_strncmp(str[i], "|", 1) == 0)
	{
		if (add_command(commands, command))
			return (NULL);
		new_command = init_command();
		if (!new_command)
			return (NULL);
		return (new_command);
	}
	if (is_redir(command, str, i))
		return (NULL);
	if (add_arg(&command, str[i]))
		return (NULL);
	return (command);
}

// str is the command line that has been split into an array of strings by spaces
int	parse_commands(char **str, t_cmds **commands)
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
