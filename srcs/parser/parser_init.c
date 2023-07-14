/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:58 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/14 18:51:23 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_cmds	*init_command(void)
{
	t_cmds	*command;

	command = (t_cmds *)malloc(sizeof(t_cmds));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->argc = 0;
	command->pipe = 0;
	command->redir = 1;
	command->redir_type = 0;
	command->redir_file = NULL;
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

static int	parse_arg(t_cmds *command, char *str)
{
	if (ft_strncmp(str, "<", 1) == 0)
		command->redir_type = 1;
	else if (ft_strncmp(str, ">", 1) == 0)
		command->redir_type = 2;
	else if (ft_strncmp(str, ">>", 2) == 0)
		command->redir_type = 3;
	else if (ft_strncmp(str, "<<", 2) == 0)
		command->redir_type = 4;
	else
	{
		command->redir = 0;
		return (add_arg(&command, str));
	}
	return (SUCCESS);
}

// str is the command line that has been split into an array of strings by spaces
int	parse_commands(char **str, t_cmds **commands)
{
	t_cmds	*command;
	int		i;

	command = init_command();
	i = 0;
	while (str[i])
	{
		if (!command)
			return (ERROR);
		if (ft_strncmp(str[i], "|", 1) == 0)
		{
			command->pipe = 1;
			if (add_command(commands, command))
				return (ERROR);
			if (str[i + 1])
				command = init_command();
		}
		else
		{
			if (parse_arg(command, str[i]))
				return (ERROR);
		}
		i++;
	}
	add_command(commands, command);
	ft_free_split(str);
	return (SUCCESS);
}
