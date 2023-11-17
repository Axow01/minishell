/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:43:57 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:43:59 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief Check if c it's a space
/// @param c is a char
/// @return 1 = true 0 = false
int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}
