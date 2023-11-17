/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:48:11 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:48:13 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/string.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!dest || !src)
		return (0);
	if (size <= ft_strlen(dest))
		return (size + ft_strlen(src));
	len = ft_strlen(dest);
	i = 0;
	while (src[i] && len + 1 < size)
	{
		dest[len] = src[i];
		i++;
		len++;
	}
	dest[len] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[i]));
}
