/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:48:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/14 18:53:40 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_cmds	*init_commands(char **str)
{
	t_cmds	*commands;

	commands = NULL;
	if (parse_commands(str, &commands))
	{
		free_commands(commands);
		return (NULL);
	}
	return (commands);
}

void	print_args(t_cmds *commands)
{
	t_cmds	*tmp;
	int		i;

	tmp = commands;
	while (tmp)
	{
		printf("\n");
		i = 0;
		while (tmp->args[i])
		{
			printf("arg[%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		printf("argc: %d\n", tmp->argc);
		printf("pipe: %d\n", tmp->pipe);
		printf("redir: %d\n", tmp->redir);
		printf("redir_type: %d\n", tmp->redir_type);
		printf("redir_file: %s\n", tmp->redir_file);
		tmp = tmp->next;
	}
}

void	parser(char **str)
{
	t_cmds	*commands;

	commands = init_commands(str);
	if (!commands)
		return ;
	print_args(commands);
	free_commands(commands);
}