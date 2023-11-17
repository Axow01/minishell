/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:57:11 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:57:13 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	char_count(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*ft_del_char(char *str, char c)
{
	char	*new;
	size_t	charnum;
	size_t	i;
	size_t	j;

	charnum = char_count(str, c);
	i = 0;
	j = 0;
	if (!str || charnum <= 0)
		return (str);
	new = mms_alloc(ft_strlen(str) - charnum + 1, sizeof(char));
	if (!new)
		return (str);
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (mms_free(str), new);
}

void	replace_space(char *str, size_t start, size_t end)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (ft_isspace(str[i]))
				str[i] = '\0';
		}
		i++;
	}
}
