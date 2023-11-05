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
	char *errc;

	i = 0;
	count = 0;
	errc = ft_itoa(get_infos()->latest_error_code);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$' && !isinquote(str, i, SINGLE_QUOTE))
			i++;
		else if (str[i] == '$' && str[i + 1] == '?' && !isinquote(str, i, SINGLE_QUOTE))
        {
            count += ft_strlen(errc);
            i++;
        }
		else if (str[i] == '$' && !isinquote(str, i, SINGLE_QUOTE))
		{
			dollars_len = dollars_key_len(&str[i + 1]);
			count += ft_strlen(check_for_key(&str[i + 1], get_infos()->env, dollars_len))  - dollars_len;
		}	
		i++;
	}
	errc = mms_free(errc);
	return (count);
}

void dollars_token_copy(char *str, char *new_line, size_t *i, size_t *j)
{
	char *token;
	size_t dollars_len;
	size_t k;

	dollars_len = dollars_key_len(&str[*i + 1]);
	k = 0;
	if (str[*i + 1] && dollars_key_exist(&str[*i + 1], dollars_len))
	{
		token = check_for_key(&str[*i + 1], get_infos()->env, dollars_len);
		while (token[k])
		{
			new_line[*j] = token[k];
			k++;
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

void dollars_qmark(char *new, size_t *i, size_t *j)
{
	size_t k;
	char *errc;

	k = 0;
	errc = ft_itoa(get_infos()->latest_error_code);
	while (errc[k])
	{
		new[*j] = errc[k];
		*j += 1;
		k++;
	}
	*i += 2;
	errc = mms_free(errc);
}