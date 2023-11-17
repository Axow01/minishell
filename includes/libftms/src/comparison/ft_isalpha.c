/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:42:31 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:42:34 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief Check if it's an alphabet
/// @param c is a char
/// @return 1 = true 0 = false
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
