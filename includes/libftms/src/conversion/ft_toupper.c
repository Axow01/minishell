/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:44:33 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:44:35 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief transform a lette in uppercase
/// @param c is a char
/// @return c if it's alrady a upper or c - 32 
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
