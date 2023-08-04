/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:04:11 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 05:28:30 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_command(t_cmds *command)
{
	if (command->args && command->args[0])
		ft_free_split(command->args);
	if (command->redir)
		free_redir(command->redir);
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

void    free_env_vars(t_env_var *env_var)
{
	t_env_var   *tmp;

	while (env_var)
	{
		tmp = env_var->next;
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		free(env_var);
		env_var = tmp;
	}
}
