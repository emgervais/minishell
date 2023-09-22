/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:40:07 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/22 12:07:00 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	in_range(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (str[0] == '-')
	{
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
			return (0);
	}
	else
	{
		if (ft_strncmp(str, "9223372036854775807", 19) > 0)
			return (0);
	}
	return (1);
}

int	ft_exit(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->argc > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	if (cmd->argc == 2)
	{
		if (ft_strlen(cmd->args[1]) > 19 || !in_range(cmd->args[1]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (255);
		}
		i = ft_atoi(cmd->args[1]);
	}
	if (cmd->next || cmd->prev)
		return (i % 256);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_all(minishell());
	exit(i);
}
