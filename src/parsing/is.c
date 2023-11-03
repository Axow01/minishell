#include "minishell.h"

bool	isredirec(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
		return (true);
	return (false);
}

bool	is_coated_quote(char *str, size_t pos)
{
	if ((str[pos] == '\'' && !isinquote(str, pos, DOUBLE_QUOTE))
			|| (str[pos] == '\"' && !isinquote(str, pos, SINGLE_QUOTE)))
		return (true);
	return (false);
}

bool	isinquote(char *str, size_t pos, size_t quote)
{
	bool	in_single_quote;
	bool	in_double_quote;
	size_t	i;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (pos == 0 || !str)
		return (false);
	while (i <= pos)
	{
		if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (quote == QUOTES && (in_single_quote || in_double_quote))
		return (true);
	else if (quote == SINGLE_QUOTE && in_single_quote)
		return (true);
	else if (quote == DOUBLE_QUOTE && in_double_quote)
		return (true);
	return (false);
}
