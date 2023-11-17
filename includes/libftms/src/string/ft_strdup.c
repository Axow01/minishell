/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:47:55 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:47:57 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/string.h"
#include "../../../libmms/libmms.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*copy;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	copy = mms_alloc(len, sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, src, len);
	return (copy);
}
