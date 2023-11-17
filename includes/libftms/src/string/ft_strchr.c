/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:47:50 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:47:52 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/string.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	n;

	if (!str)
		return (NULL);
	i = 0;
	n = ft_strlen(str);
	while (i <= n)
	{
		if (((char *)str)[i] == (unsigned char)c)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
