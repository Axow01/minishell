/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:45:17 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:45:20 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_numlen(unsigned long long nbr)
{
	unsigned int		i;
	unsigned long long	nb;

	i = 0;
	if (nbr == 0)
		return (1);
	else
		nb = nbr;
	while (nb != 0)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

int	ft_putpointer(unsigned long long nbr)
{
	char				*hex;
	unsigned long long	nb;

	nb = nbr;
	hex = "0123456789abcdef";
	if (nb >= 16)
		ft_putpointer(nb / 16);
	ft_putchar_fd(hex[nb % 16], 1);
	return (ft_numlen(nbr));
}
