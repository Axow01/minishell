
#include "minishell.h"
#include <stdio.h>
#include <string.h>

t_temp	*get_redirec(void)
{
	static t_temp	tmp;

	return (&tmp);
}

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

int	count_len(char *str)
{
	size_t i;
	size_t count;
	bool in_single_quote;
	bool in_double_quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (str[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i], "<<", 2) == 0)
			{
				count++;
				i += 2;
			}
			else if (str[i] == '>' || str[i] == '<')
				count++;
			else if (ft_isspace(str[i]))
				count++;
		}
		i++;
	}
	return (count);
}

void	teststrtok(char *str)
{
	int i;

	i = 1;
	get_infos()->cmd.cmd = mms_alloc(count_len(str), sizeof(char *));
	get_infos()->cmd.cmd[0] = ft_strtok(str, '|');
	while (get_infos()->cmd.cmd[i] != NULL)
	{
		printf("token : %s\n", get_infos()->cmd.cmd[i]);
		get_infos()->cmd.cmd[i] = ft_strtok(NULL, '|');
		i++;
	}
}