/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:48:57 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:48:59 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/string.h"
#include "../../../libmms/libmms.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	str_len;

	str_len = ft_strlen(str);
	if (!str)
		return (NULL);
	if (start > str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = (str_len - start);
	new = mms_alloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, str + start, len);
	new[len] = '\0';
	return (new);
}
