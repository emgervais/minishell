/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:04:11 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/14 17:46:21 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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
	if (command->redir_file)
		free(command->redir_file);
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