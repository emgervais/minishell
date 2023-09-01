/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:00:57 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 18:39:39 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*init_command(void)
{
	t_cmds	*command;

	command = (t_cmds *)malloc(sizeof(t_cmds));
	if (!command)
		return (NULL);
	command->fd.fd_in = STDIN_FILENO;
	command->fd.fd_out = STDOUT_FILENO;
	command->fd.status = 0;
	command->fd.pid = 0;
	command->args = NULL;
	command->argc = 0;
	command->builtin = NO_BUILTIN;
	command->redir = NULL;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

int	add_arg(t_cmds **command, char *arg)
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
	if (!tmp[i])
		return (ERROR);
	tmp[i + 1] = NULL;
	if ((*command)->args)
		free((*command)->args);
	(*command)->args = tmp;
	(*command)->argc++;
	return (SUCCESS);
}

int	add_command(t_cmds **commands, t_cmds *command)
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

int	init_redir(t_redir **redir, t_redir_type type, char *file)
{
	*redir = (t_redir *)malloc(sizeof(t_redir));
	if (!*redir)
		return (ERROR);
	(*redir)->type = type;
	(*redir)->file = remove_quotes_arg(file, ft_strdup(""));
	if (!(*redir)->file)
		return (ERROR);
	(*redir)->next = NULL;
	return (SUCCESS);
}

int	add_redir(t_cmds **command, t_redir *redir)
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
