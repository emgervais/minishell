/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/21 12:12:27 by ele-sage         ###   ########.fr       */
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

void	check_double_quotes(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		is_var_in_double_quotes(str[i]);
		i++;
	}
}