/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:52:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/18 18:43:49 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_double_quotes(char **args)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	while(args[i])
	{
		j = 0;
		k = 0;
		len = ft_strlen(args[i]);
		while(args[i][j])
		{
			if(args[i][j] == '\'')
			{
				args[i][k++] = args[i][j++];
				while(args[i][j] && args[i][j] != '\'')
					args[i][k++] = args[i][j++];
				args[i][k++] = args[i][j++];
			}
			else if(args[i][j] == '\"')
			{
				j++;
				while(args[i][j] && args[i][j] != '\"')
					args[i][k++] = args[i][j++];
				j++;
			}
			else
				args[i][k++] = args[i][j++];
		}
		args[i][k] = '\0';
		i++;
	}
}