/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:48:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 23:19:16 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *str, t_cmds *command)
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
    add_arg(&command, str);
	return (1);
}

static t_cmds *is_redir(t_cmds *command, char **str, int *i)
{
    t_redir_type    type;
	t_redir         *redir;

    if (ft_strncmp(str[*i], ">>", 3) == 0)
        type = APPEND;
    else if (ft_strncmp(str[*i], "<<", 3) == 0)
        type = HEREDOC;
    else if (ft_strncmp(str[*i], ">", 2) == 0)
        type = OUT;
    else if (ft_strncmp(str[*i], "<", 2) == 0)
        type = IN;
    else
        return (NULL);
	if (init_redir(&redir, type, str[++(*i)]))
		return (NULL);
	if (add_redir(&command, redir))
		return (NULL);
    return (command);
}

static t_cmds *parse_arg(t_cmds **commands, t_cmds *command, char **str, int *i)
{
    t_cmds  *new_command;

    if (is_redir(command, str, i))
        return (command);
    if (str[*i][0] == '|' && str[*i][1] == '\0')
    {
        if (add_command(commands, command))
            return (NULL);
        if (str[*i + 1] != NULL)
        {
            new_command = init_command();
            if (!new_command)
                return (NULL);
            return (new_command);
        }
        return (command);
    }
    if (command->argc == 0 && is_builtin(str[*i], command))
        return (command);
    if (add_arg(&command, str[*i]))
        return (NULL);
	return (command);
}

static int  parse_commands(char **str, t_cmds **commands)
{
    t_cmds  *command;
    int     i;

    command = init_command();
    if (!command)
        return (ERROR);
    i = 0;
    while (str[i])
    {
        command = parse_arg(commands, command, str, &i);
        if (!command)
            return (ERROR);
        i++;
    }
    if (add_command(commands, command))
        return (ERROR);
    return (SUCCESS);
}

int		parser(char **str, t_cmds **cmds)
{
	t_cmds	*commands;
    int     ret;

	commands = NULL;
    ret = SUCCESS;
	if (parse_commands(str, &commands))
        ret = ERROR;
    ft_free_split(str);
    if (ret == SUCCESS)
        *cmds = commands;
    else
        free_commands(commands);
    return (ret);
}