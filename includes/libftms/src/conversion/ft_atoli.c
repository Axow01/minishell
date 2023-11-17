/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:44:17 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:44:18 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/comparison.h"

static long int	check(char *str, long int i)
{
	long int	res;

	res = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

/// @brief alphabet to long integer
/// @param str is a string whit dedgit
long int	ft_atoli(const char *str)
{
	int			sign;
	long int	i;

	sign = 1;
	i = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		sign = 1;
		i++;
	}
	return (check((char *)str, i) * sign);
}
