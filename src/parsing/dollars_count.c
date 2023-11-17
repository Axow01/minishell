#include "minishell.h"

static	void	dollars_count_logical(char *str, char *errc, size_t *count)
{
	size_t	i;
	size_t	dollars_len;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$' && !isinquote(str, i,
				SINGLE_QUOTE))
			i++;
		else if (str[i] == '$' && str[i + 1] == '?' && !isinquote(str, i,
				SINGLE_QUOTE))
		{
			*count += ft_strlen(errc);
			i++;
		}
		else if (str[i] == '$' && !isinquote(str, i, SINGLE_QUOTE))
		{
			dollars_len = dollars_key_len(&str[i + 1]);
			*count += ft_strlen(check_for_key(&str[i + 1], get_infos()->env,
						dollars_len)) - dollars_len;
		}
		if (str[i])
			i++;
	}
}

size_t	dollars_count(char *str)
{
	size_t	count;
	char	*errc;

	count = 0;
	errc = ft_itoa(get_infos()->latest_error_code);
	dollars_count_logical(str, errc, &count);
	errc = mms_free(errc);
	return (count + 2);
}
