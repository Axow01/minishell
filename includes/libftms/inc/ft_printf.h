/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:50:37 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:50:39 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "write_fd.h"

//prototype

int	ft_putnbr_base(unsigned int nbr, char c);
int	ft_printf(const char *str, ...);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putpointer(unsigned long long n);

#endif