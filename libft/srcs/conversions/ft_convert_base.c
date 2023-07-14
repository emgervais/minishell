/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:16:27 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:28:07 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static int	ft_is_valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || ft_is_space(base[i]))
			return (0);
		while (base[j])
		{
			if (base[i] == base[j] && i != j)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	ft_get_base_len(char *base, int *neg, int *nbr)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	*neg = 1;
	if (*nbr < 0)
	{
		*neg = -1;
		*nbr *= -1;
	}
	return (i);
}

static int	ft_get_base_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_convert_base(int nbr, char *base_from, char *base_to)
{
	int	i;
	int	neg;
	int	res;
	int	base_len;

	i = 0;
	res = 0;
	base_len = ft_get_base_len(base_to, &neg, &nbr);
	if (ft_is_valid_base(base_from) && ft_is_valid_base(base_to))
	{
		while (nbr)
		{
			res += ft_get_base_index(nbr % base_len, base_to)
				* ft_power(base_len, i);
			nbr /= base_len;
			i++;
		}
		return (res * neg);
	}
	return (0);
}
