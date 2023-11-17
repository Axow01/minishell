/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:45:31 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:45:32 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_stringf.h"
#include "../../../libmms/libmms.h"

char	*sort_c(int val, char *str, size_t i)
{
	char	*new;

	if (!str)
		return (NULL);
	new = mms_alloc(ft_strlen(str), sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, i);
	new[i] = val;
	if (ft_strlen(&str[i + 2]) > 0)
		ft_memcpy(&new[i + 1], &str[i + 2], ft_strlen(&str[i + 2]));
	return (new);
}

char	*sort_s(char *val, char *str, size_t i)
{
	char	*new;

	if (!str)
		return (NULL);
	new = mms_alloc(i + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, i);
	new = ft_gnl_strjoin(new, val);
	if (ft_strlen(&str[i + 2]) > 0)
		new = ft_gnl_strjoin(new, &str[i + 2]);
	return (new);
}

char	*sort_d(int val, char *str, size_t i)
{
	char	*new;
	char	*num;

	num = ft_itoa(val);
	if (!str || !num)
		return (NULL);
	new = mms_alloc(i + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, i);
	new = ft_gnl_strjoin(new, num);
	if (ft_strlen(&str[i + 2]) > 0)
		new = ft_gnl_strjoin(new, &str[i + 2]);
	mms_free(num);
	return (new);
}

char	*sort(va_list *arg, char *str, char c, size_t i)
{
	if (c == 'c')
		return (sort_c(va_arg(*arg, int), str, i));
	else if (c == 's')
		return (sort_s(va_arg(*arg, char *), str, i));
	else if (c == 'S')
		return (sort_cs(va_arg(*arg, char *), str, i));
	else if (c == 'd')
		return (sort_d(va_arg(*arg, int), str, i));
	return (str);
}

char	*ft_stringf(const char *str, ...)
{
	size_t	i;
	va_list	arg;
	char	*new;
	char	*temp;

	i = 0;
	if (!str)
		return (NULL);
	new = ft_strdup(str);
	if (!new)
		return (NULL);
	va_start(arg, str);
	while (new[i])
	{
		if (new[i] == '%')
		{
			temp = new;
			new = sort(&arg, new, new[i + 1], i);
			mms_free(temp);
		}
		i++;
	}
	va_end(arg);
	return (new);
}
