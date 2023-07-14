/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:01:11 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/21 16:19:22 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERSIONS_H
# define FT_CONVERSIONS_H

# include "libft.h"

/*/////////////////////////////////////////////////////////////////////////////
		CONVERSION FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

long	ft_atol(const char *str);
int		ft_big_atoi(const char *str);
long	ft_big_atol(const char *str);
int		ft_convert_base(int nbr, char *base_from, char *base_to);
void	ft_swap(int *a, int *b);
char	*ft_str_toupper(const char *str);
char	*ft_str_tolower(const char *str);
int		ft_add_str_to_int(const char *str, int *a);
float	ft_atof(const char *str);
void	ft_replace_char(char *str, char c, char rep);

#endif //FT_CONVERSIONS_H