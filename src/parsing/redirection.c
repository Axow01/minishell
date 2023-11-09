#include "minishell.h"

size_t	count_redirection(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == '|')
			{
				count += 2;
			}
			while (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i],
					"<<", 2) == 0)
			{
				count += 2;
				i += 2;
			}
			if (str[i] == '>' || str[i] == '<')
				count += 2;
		}
		i++;
	}
	return (count);
}

bool	check_valid_redirec(t_command *head)
{
	size_t	i;

	i = 0;
	while (head->tmp[i])
	{
		if (head->tmp[i + 1] && head->tmp[i][0])
			if (isredirec(head->tmp[i]) > 0 && isredirec(head->tmp[i + 1]) > 0)
			{
				printf("%s`%s'\n", ERROR_BASE_MSG, head->tmp[i + 1]);
				return (false);
			}
		i++;
	}
	if (i > 0 && head->tmp[i - 1] && isredirec(head->tmp[i - 1]) > 0)
		return (printf("%s`newline'\n", ERROR_BASE_MSG), false);
	return (true);
}

void	fd_maker(t_command *head)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = 0;
	while (head->tmp[i])
	{
		if (head->tmp[i][0] && isredirec(head->tmp[i]) > 0)
		{
			if (fd > 2)
				close(fd);
			if (isredirec(head->tmp[i]) == 1 && head->tmp[i][0] == '>')
			{
				fd = open(head->tmp[i + 1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
				head->stdout_ = fd;
			}
			else if (isredirec(head->tmp[i]) == 1 && head->tmp[i][0] == '<')
			{
				fd = open(head->tmp[i + 1], O_RDONLY);
				head->stdin_ = fd;
			}
			else if (isredirec(head->tmp[i]) == 2 && head->tmp[i][0] == '>')
			{
				fd = open(head->tmp[i + 1], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
				head->stdout_ = fd;
			}
			if (fd < 0)
				break ;
		}
		i++;
	}
	if (fd < 0)
		printf("minishell: %s: %s\n", head->tmp[i + 1], ERROR_DIR_MSG);
}
