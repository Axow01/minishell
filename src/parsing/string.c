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

void	remove_quote(t_command *head)
{
	size_t i;
	size_t j;
	size_t k;
	char *new;

	i = 0;
	while (head && head->tmp && head->tmp[i])
	{
		j = 0;
		k = 0;
		new = mms_alloc(ft_strlen(head->tmp[i]) + 1, sizeof(char));
		while (head->tmp[i][j])
		{
			if (!is_coated_quote(head->tmp[i], j))
				new[k++] = head->tmp[i][j];
			j++;
		}
		mms_free(head->tmp[i]);
		head->tmp[i] = new;
		i++;
	}
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