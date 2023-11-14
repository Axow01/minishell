#include "minishell.h"

size_t	count_nonerdt_token(char **token)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (token && token[i])
	{
		if (isredirec(token[i]))
			i++;
		else
			count++;
		if (token[i])
			i++;
	}
	return (count);
}

void	get_token(char *line, size_t start, size_t end, t_command *head)
{
	size_t	i;
	size_t	j;
	size_t	ptr;

	i = start;
	j = 0;
	while (line[i] == '\0' && i < end)
		i++;
	ptr = i;
	while (i <= end)
	{
		if (line[i] == '\0')
		{
			head->tmp[j++] = ft_strdup(&line[ptr]);
			while (line[i] == '\0' && i < end)
				i++;
			ptr = i;
		}
		i++;
	}
}

size_t	ctoken(char *line, size_t start, size_t end)
{
	size_t	i;
	size_t	count;

	i = start;
	count = 1;
	while (line[i] == '\0' && i < end)
		i++;
	while (i < end)
	{
		if (line[i] == '\0')
		{
			while (line[i] == '\0' && i < end)
				i++;
			if (i < end)
				count++;
		}
		i++;
	}
	return (count);
}
