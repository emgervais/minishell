/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:04:11 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/20 22:14:05 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_cmds *command)
{
	int	i;

	i = 0;
	if (command->args)
	{
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
	if (command->redir)
	{
		while (command->redir)
		{
			free(command->redir->file);
			free(command->redir);
			command->redir = command->redir->next;
		}
	}
	free(command);
}

void	free_commands(t_cmds *commands)
{
	t_cmds	*tmp;

	while (commands)
	{
		tmp = commands->next;
		free_command(commands);
		commands = tmp;
	}
}

void    free_all_env_vars(t_env_var *env_var)
{
    t_env_var    *tmp;

    while (env_var)
    {
        tmp = env_var->next;
        free(env_var->key);
        free(env_var->value);
        free(env_var);
        env_var = tmp;
    }
}

