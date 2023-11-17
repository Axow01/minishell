/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:44:28 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:44:30 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief transform a lette in lowercase
/// @param c is a char
/// @return c if it's alrady a lower or c + 32 
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
