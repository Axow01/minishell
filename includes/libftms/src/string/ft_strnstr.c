/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:48:39 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:48:41 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/string.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	if (!haystack && !needle)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (needle_len == 0 || haystack == needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (i + needle_len > len)
			return (NULL);
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
