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
