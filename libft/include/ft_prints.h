/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:01:48 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:43:31 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTS_H
# define FT_PRINTS_H

# include "libft.h"

/*/////////////////////////////////////////////////////////////////////////////
		PRINT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

int		ft_int_putchar(int c);
int		ft_int_putchar_fd(int c, int fd);

//int	ft_int_putptr_base_fd(unsigned long long nbr, char *base, int fd);
int		ft_int_putptr_fd(unsigned long long nbr, int fd);

//void	ft_putptr_base_fd(unsigned long long nbr, char *base, int fd);
void	ft_putptr_fd(unsigned long long nbr, int fd);

//int	ft_int_putptr_base(unsigned long long nbr, char *base);
int		ft_int_putptr(unsigned long long nbr);

void	ft_putnbr_base_fd(unsigned int nbr, char *base, int fd);
int		ft_int_putnbr_base(unsigned int nbr, char *base);
int		ft_int_putnbr_base_fd(unsigned int nbr, char *base, int fd);

int		ft_int_putnbr(int n);
int		ft_int_putnbr_fd(int n, int fd);

int		ft_int_putstr(char *s);
int		ft_int_putstr_fd(char *s, int fd);

#endif //FT_PRINTS_H