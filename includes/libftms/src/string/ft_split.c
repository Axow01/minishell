/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:47:41 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:47:43 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/string.h"
#include "../../../libmms/libmms.h"

static int	num_word(char const *str, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			num++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (num);
}

static char	**clean(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		mms_free(tab[i]);
		i++;
	}
	mms_free(tab);
	return (NULL);
}

static char	**check(char **dest, char *str, int word, int c)
{
	int	last_pos;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < word)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			last_pos = i;
		while (str[i] && str[i] != c)
			i++;
		if (j < word)
		{
			dest[j] = ft_substr((char *)str, last_pos, i - (last_pos));
			if (!dest[j])
				return (clean(dest));
			j++;
		}
	}
	return (dest);
}

/// @brief split a string and store all new string in to a double pointer
/// @param str is the innitial string
/// @param c is the separator
/// @return the double pointer
char	**ft_split(char const *str, char c)
{
	char	**new_tab;
	int		word;

	if (!str)
		return (NULL);
	word = num_word(str, c);
	new_tab = mms_alloc(word + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	return (check(new_tab, (char *)str, word, c));
}
