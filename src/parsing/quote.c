#include "minishell.h"

char	*remove_quote_token(char *token)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	new = mms_alloc(ft_strlen(token) + 1, sizeof(char));
	while (token[i])
	{
		if (!is_coated_quote(token, i))
			new[j++] = token[i];
		i++;
	}
	return (new);
}

void	remove_quote(t_command *head)
{
	size_t	i;
	char	*new;

	i = 0;
	while (head && head->tmp && head->tmp[i])
	{
		new = remove_quote_token(head->tmp[i]);
		mms_free(head->tmp[i]);
		head->tmp[i] = new;
		i++;
	}
	i = 0;
	while (head && head->cmd && head->cmd[i])
	{
		new = remove_quote_token(head->cmd[i]);
		mms_free(head->cmd[i]);
		head->cmd[i] = new;
		i++;
	}
}
