/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:55:45 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/05 16:08:25 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char c)
{
	char	sep[5];
	int		i;

	sep[0] = '|';
	sep[1] = ' ';
	sep[2] = '<';
	sep[3] = '>';
	sep[4] = 0;
	i = 0;
	while (sep[i])
		if (c == sep[i++])
			return (1);
	return (0);
}

int	llen(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (*str && !is_sep(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			i = lal(str);
			str += i;
			c += i;
		}
		str++;
		c++;
	}
	if (!c)
	{
		i++;
		while (str[i] == *str)
			i++;
		return (i);
	}
	return (c);
}

static int	valid_sep(char *in)
{
	int	i;

	i = 0;
	while (*in && *in == ' ')
		in++;
	while (is_sep(in[i]) && in[i] != ' ')
	{
		i++;
		if (((*in == '<' || *in == '>') && i > 2)
			|| (*in == '|' && in[i] == '|'))
			return (syntax_error_lexer(*in));
	}
	while (in[i] && in[i] == ' ')
		i++;
	if (((*in == '>' || *in == '>') && is_sep(in[i])) || in[i] == '|')
		return (syntax_error_lexer(*in));
	return (1);
}

static int	count_args(char *in, int count)
{
	while (*in)
	{
		if (*in == '\'' || *in == '\"')
		{
			if (skip(in, 0) == -1)
				return (0);
			in += skip(in, 0);
			if (!*in || is_sep(*in))
				count++;
		}
		else if (is_sep(*in))
		{
			if (!valid_sep(in))
				return (0);
			count += skip(in, 1);
			in = norm(in, 0);
			in = norm(in, 1);
		}
		else
		{
			in = norm(in, 2);
			count += skip(in, 2);
		}
	}
	return (count);
}

char	**lexer(char *input)
{
	char	**a;
	int		len;

	if (!input)
		return (NULL);
	len = count_args(input, 0);
	if (!len)
		return (NULL);
	a = malloc(sizeof(char *) * (len + 1));
	if (!a)
		return (NULL);
	if (write_in(input, a))
		return (NULL);
	return (a);
}
