#include "minishell.h"

int	isredirec(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
		return (1);
	return (0);
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

bool	is_valid(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (isredirec(&str[i]) > 0 && !isinquote(str, i, QUOTES))
		{
			i += isredirec(&str[i]);
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] && isredirec(&str[i]) > 0)
			{
				if (isredirec(&str[i]) == 1)
					printf("%s`%c'\n", ERROR_BASE_MSG, str[i]);
				else
					printf("%s`%c%c'\n", ERROR_BASE_MSG, str[i], str[i + 1]);
				return (false);
			}
		}
		if (str[i])
			i++;
	}
	if (isinquote(str, i, QUOTES))
		return (printf("%s(\"or')\n", ERROR_QUOTE_MSG), false);
	return (true);
}
