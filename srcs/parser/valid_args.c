/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/14 18:04:04 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"


static void remove_double_quotes_from_arg(char *arg)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			i++;
		arg[j] = arg[i];
		i++;
		j++;
	}
	arg[j] = '\0';
}


static void remove_single_quotes_from_arg(char *arg)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			i++;
		arg[j] = arg[i];
		i++;
		j++;
	}
	arg[j] = '\0';
}

void	verify_args(t_cmds *commands)
{
	t_cmds	*tmp;
	int		i;

	tmp = commands;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{

			i++;
		}
		tmp = tmp->next;
	}
}

void	verify_commands(t_cmds *commands)
{
	t_cmds	*tmp;

	tmp = commands;
	while (tmp)
	{
		verify_args(tmp);
		tmp = tmp->next;
	}
}