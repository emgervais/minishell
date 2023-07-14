/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:12:34 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:35 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_print_parse(va_list ap, char fc)
{
	int	count;

	count = 0;
	if (fc == 's')
		count += ft_int_putstr(va_arg(ap, char *));
	else if (fc == 'c')
		count += ft_int_putchar(va_arg(ap, int));
	else if (fc == 'd' || fc == 'i')
		count += ft_int_putnbr(va_arg(ap, int));
	else if (fc == 'u')
		count += ft_int_putnbr_base(va_arg(ap, unsigned int), BASEDEC);
	else if (fc == 'x')
		count += ft_int_putnbr_base(va_arg(ap, unsigned int), LOWERHEX);
	else if (fc == 'X')
		count += ft_int_putnbr_base(va_arg(ap, unsigned int), UPPERHEX);
	else if (fc == 'p')
		count += ft_int_putptr((unsigned long long)va_arg(ap, void *));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	size_t	a;

	count = 0;
	a = 0;
	va_start(ap, format);
	while (format[a])
	{
		if (format[a] == '%')
		{
			a++;
			if (format[a] == '%')
				count += ft_int_putchar(format[a]);
			else if (ft_ischarset(format[a], PRINTFCSET))
				count += ft_print_parse(ap, format[a]);
			else if (!format[a])
				break ;
		}
		else
			count += ft_int_putchar(format[a]);
		a++;
	}
	va_end(ap);
	return (count);
}
