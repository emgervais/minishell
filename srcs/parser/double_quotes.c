/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/18 16:51:09 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void remove_double_quotes_from_arg(char *arg)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (arg[i] == '\"')
			i++;
		arg[j] = arg[i];
		i++;
		j++;
	}
	arg[j] = '\0';
}

static void	is_var_in_double_quotes(char *str)
{
	int	len;
	int	i;
	
	len = ft_strlen(str);
	i = 0;
	//printf("str: %s\n", str);
	if (str[0] == '\"')
	{
		while (i < len-3)
		{
			if (str[i] == '$')
				break;
			i++;
		}
		if (str[i] == '$')
			remove_double_quotes_from_arg(str);
		else
		{
			str[0] = '\'';
			str[len-1] = '\'';
		}
	}
}

void	check_double_quotes(t_cmds *commands)
{
	t_cmds	*tmp;
	int		i;

	tmp = commands;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
			is_var_in_double_quotes(tmp->args[i++]);
		tmp = tmp->next;
	}
}