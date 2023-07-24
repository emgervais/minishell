/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:48:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/24 14:17:21 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (tmp->redir)
		{
			printf("redir: %d\n", tmp->redir->type);
			printf("file: %s\n", tmp->redir->file);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
}

t_cmds	*parser(char **str)
{
	t_cmds		*commands;

	commands = init_commands(str);
	ft_free_split(str);
	if (!commands)
		return (NULL);
	print_args(commands);
	return (commands);
}