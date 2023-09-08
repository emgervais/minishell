/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:21:34 by egervais          #+#    #+#             */
/*   Updated: 2023/09/07 22:12:36 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	echo_option(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-' || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_cmds *cmds)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	if (cmds->argc > 1)
	{
		while (n < cmds->argc && echo_option(cmds->args[n]))
			n++;
		i = n;
		while (i < cmds->argc)
		{
			ft_putstr_fd(cmds->args[i], cmds->fd.fd_out);
			if (i + 1 < cmds->argc)
				ft_putchar_fd(' ', cmds->fd.fd_out);
			i++;
		}
	}
	if (n == 1)
		ft_putchar_fd('\n', cmds->fd.fd_out);
	minishell()->status = 0;
	return (SUCCESS);
}
