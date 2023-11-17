/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:45:04 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:45:06 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	ft_hex_len(unsigned int nbr)
{
	unsigned int	i;
	unsigned int	nb;

	i = 1;
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

int	ft_putnbr_base(unsigned int nbr, char c)
{
	char			*hex;
	unsigned int	nb;

	nb = nbr;
	if (c == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (nb >= 16)
		ft_putnbr_base(nb / 16, c);
	ft_putchar_fd(hex[nb % 16], 1);
	return (ft_hex_len(nbr));
}
