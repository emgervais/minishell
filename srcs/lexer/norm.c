/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:08:41 by egervais          #+#    #+#             */
/*   Updated: 2023/09/05 12:32:50 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lal(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != *str)
		i++;
	if (!str[i])
		return (0);
	return (i);
}

int	skip(char *in, int mode)
{
	int	i;

	i = 1;
	if (mode == 0)
	{
		while (in[i] && in[i] != *in)
			i++;
		if (!in[i])
			return (-1);
		return (i + 1);
	}
	if (mode == 1)
	{
		if (is_sep(*in))
			return (1);
		return (0);
	}
	else
	{
		if (is_sep(*in) || !*in)
			return (1);
		return (0);
	}
}

int	write_in(char *input, char **a)
{
	int		i;
	int		len;
	int		k;
	char	*line;

	k = 0;
	while (*input)
	{
		i = 0;
		while (*input && *input == ' ')
			input++;
		len = llen(input);
		line = malloc(sizeof(char) * (len + 1));
		if (!line)
			return (ft_free_split(a), 1);
		line[len] = '\0';
		while (i < len)
		{
			line[i++] = *input;
			input++;
		}
		a[k++] = line;
	}
	a[k] = NULL;
	return (0);
}

char	*norm(char *in, int mode)
{
	if (mode == 0)
	{
		if (in[1] == *in && is_sep(*in))
			in += 2;
		else
			in++;
		return (in);
	}
	if (mode == 1)
	{
		while (*in && *in == ' ')
			in++;
		return (in);
	}
	while (*in && !is_sep(*in) && *in != '\'' && *in != '\"')
		in++;
	return (in);
}
