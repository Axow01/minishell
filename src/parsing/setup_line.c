#include "minishell.h"

static void	not_inquote_side(char *str, char *new_line, size_t *i, size_t *j)
{
	if (str[*i] && !isinquote(str, *i, QUOTES))
	{
		if (str[*i] == '|' && !isinquote(str, *i, QUOTES))
		{
			new_line[(*j)++] = ' ';
			new_line[(*j)++] = str[(*i)++];
			new_line[(*j)++] = ' ';
		}
		while (ft_strncmp(&str[*i], ">>", 2) == 0 || ft_strncmp(&str[*i], "<<",
				2) == 0)
		{
			new_line[(*j)++] = ' ';
			new_line[(*j)++] = str[(*i)++];
			new_line[(*j)++] = str[(*i)++];
			new_line[(*j)++] = ' ';
		}
		if (str[*i] == '>' || str[*i] == '<')
		{
			new_line[(*j)++] = ' ';
			new_line[(*j)++] = str[(*i)++];
			new_line[(*j)++] = ' ';
		}
	}
}

static void	dollars_side(char *str, char *new_line, size_t *i, size_t *j)
{
	while (str[*i] == '$' && !isinquote(str, *i, SINGLE_QUOTE))
	{
		if (str[*i] == '$' && str[*i + 1] == '$' && !isinquote(str, *i,
				SINGLE_QUOTE))
		{
			new_line[(*j)++] = '$';
			*i += 2;
		}
		else if (str[*i] == '$' && str[*i + 1] == '?' && !isinquote(str, *i,
				SINGLE_QUOTE))
			dollars_qmark(new_line, i, j);
		else if (str[*i] == '$' && !isalpha(str[*i + 1]))
		{
			new_line[(*j)++] = '$';
			*i += 1;
		}
		else if (str[*i] == '$' && !isinquote(str, *i, SINGLE_QUOTE))
			dollars_token_copy(str, new_line, i, j);
	}
}

char	*setup_line(char *str, size_t *len)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	*len = (count_redirection(str) + ft_strlen(str) + dollars_count(str) + 1);
	if (*len == 0)
		return (NULL);
	new_line = mms_alloc(*len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str && str[i])
	{
		not_inquote_side(str, new_line, &i, &j);
		dollars_side(str, new_line, &i, &j);
		if (str[i] && (str[i] != '$' || str[i] != '\'' || str[i] != '\"'))
			new_line[j++] = str[i++];
	}
	return (new_line);
}
