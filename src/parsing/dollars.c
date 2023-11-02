#include "minishell.h"

char	*check_for_key(char *key, char **env, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (j == len && ft_strncmp(env[i], key, j) == 0)
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}

size_t dollars_key_len(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			break;
		i++;
	}
	return (i);
}

bool dollars_key_exist(char *key, size_t len)
{
	if (check_for_key(key, get_infos()->env, len) && len > 0)
		return (true);
	return (false);
}

size_t dollars_count(char *str)
{
	size_t i;
	size_t count;
	size_t dollars_len;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$' && !isinquote(str, i, SINGLE_QUOTE))
			i += 2;
		else if (str[i] == '$' && !isinquote(str, i, SINGLE_QUOTE))
		{
			dollars_len = dollars_key_len(&str[i + 1]);
			// printf("dol : %d\n", dollars_key_exist(&str[i + 1], dollars_len));
			// printf("dolen : %zu\n", dollars_len);
			count += ft_strlen(check_for_key(&str[i + 1], get_infos()->env, dollars_len)) - (dollars_len);
		}	
		i++;
	}
	return (count);
}

void dollars_token_copy(char *str, char *new_line, size_t *i, size_t *j)
{
	char *token;
	size_t dollars_len;

	dollars_len = dollars_key_len(&str[*i + 1]);
	if (dollars_key_exist(&str[*i + 1], dollars_len) && str[*i + 1])
	{
		token = check_for_key(&str[*i + 1], get_infos()->env, dollars_len);
		while (*token)
		{
			new_line[*j] = *token;
			token++;
			*j += 1;
		}
		*i += dollars_len + 1;
	}
	else if (!dollars_key_exist(&str[*i + 1], dollars_len) || !str[*i + 1])
	{
		if (dollars_len > 0)
			*i += dollars_len + 1;
		else
			*i += 1;
		return ;
	}
}