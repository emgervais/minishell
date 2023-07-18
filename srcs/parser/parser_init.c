/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:58 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/18 16:02:36 by ele-sage         ###   ########.fr       */
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
	command->pipe = 0;
	command->redir = 0;
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

static int is_redir(t_cmds *command, char **str, int i)
{
	command->redir = 1;
	if (ft_strncmp(str[i], ">>", 2) == 0)
		command->redir_type = 3;
	else if (ft_strncmp(str[i], "<<", 2) == 0)
		command->redir_type = 4;
	else if (ft_strncmp(str[i], "<", 1) == 0)
		command->redir_type = 1;
	else if (ft_strncmp(str[i], ">", 1) == 0)
		command->redir_type = 2;
	else
		command->redir = 0;
	if (command->redir)
	{
		command->redir_file = ft_strdup(str[i + 1]);
		return (1);
	}
	return (0);
}

static t_cmds *parse_arg(t_cmds **commands, t_cmds *command, char **str, int i)
{
	t_cmds	*new_command;

	if (ft_strncmp(str[i], "|", 1) == 0)
		command->pipe = 1;
	else if (is_redir(command, str, i))
		new_command = NULL;
	else
	{
		if (add_arg(&command, str[i]))
			return (NULL);
		return (command);
	}
	if (add_command(commands, command))
		return (NULL);
	new_command = init_command();
	if (!new_command)
		return (NULL);
	return (new_command);

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
	ft_free_split(str);
	return (SUCCESS);
}
