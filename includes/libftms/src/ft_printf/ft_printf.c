/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:44:57 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:44:59 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "../../inc/ft_printf.h"

int	check(va_list arg, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(arg, int), 1));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(arg, char *), 1));
	else if (c == 'p')
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd('x', 1);
		return (ft_putpointer(va_arg(arg, unsigned long long)) + 2);
	}
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(arg, int), 1));
	else if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(arg, int)));
	else if (c == 'x' || c == 'X')
		return (ft_putnbr_base(va_arg(arg, unsigned long long), c));
	else if (c == '%')
		return (ft_putchar_fd('%', 1));
	else
		return (0);
	return (0);
}

/// @brief own version of printf 
/// @param str is't a string with or without param
/// @param ... in order all % paramater (%c, %s, %p, %d, %u, %x, %X, %%)
/// @return length of final string
int	ft_printf(const char *str, ...)
{
	int		i;
	size_t	len;
	va_list	arg;

	i = 0;
	len = 0;
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += check(arg, str[i + 1]);
			i += 2;
		}
		else
			len += ft_putchar_fd(str[i++], 1);
	}
	va_end(arg);
	return (len);
}
