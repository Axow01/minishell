/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:49:12 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:49:14 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/write_fd.h"

/// @brief write a char on a fd
/// @param c is the char
/// @param fd is the file descriptor
/// @return the write length
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
