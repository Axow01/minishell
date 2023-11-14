#include "minishell.h"

size_t	count_redirection(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == '|')
				count += 2;
			while (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i],
					"<<", 2) == 0)
			{
				count += 2;
				i += 2;
			}
			if (str[i] == '>' || str[i] == '<')
				count += 2;
		}
		if (str[i])
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
				return (printf_error(258, "%s`%s'\n", ERROR_BASE_MSG,
						head->tmp[i + 1]), false);
		i++;
	}
	if (i > 0 && head->tmp[i - 1] && isredirec(head->tmp[i - 1]) > 0)
	{
		return (printf_error(258, "%s`newline'\n", ERROR_BASE_MSG), false);
	}
	return (true);
}

static int	fd_open(t_command *head, int fd, int i)
{
	if (isredirec(head->tmp[i]) == 1 && head->tmp[i][0] == '>')
	{
		if (fd > 2 && fd != head->stdin_)
			mms_close(fd);
		fd = mms_open(head->tmp[i + 1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
		head->stdout_ = fd;
	}
	else if (isredirec(head->tmp[i]) == 1 && head->tmp[i][0] == '<')
	{
		if (fd > 2 && fd != head->stdout_)
			mms_close(fd);
		fd = mms_open(head->tmp[i + 1], O_RDONLY, 0);
		head->stdin_ = fd;
	}
	else if (isredirec(head->tmp[i]) == 2 && head->tmp[i][0] == '>')
	{
		if (fd > 2 && fd != head->stdin_)
			mms_close(fd);
		fd = mms_open(head->tmp[i + 1], O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
		head->stdout_ = fd;
	}
	return (fd);
}

void	fd_maker(t_command *head)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = 0;
	while (head->tmp && head->tmp[i])
	{
		if (head->tmp[i][0] && isredirec(head->tmp[i]) > 0)
		{
			fd = fd_open(head, fd, i);
			if (fd < 0)
				break ;
		}
		i++;
	}
	if (fd < 0)
		printf("minishell: %s: %s\n", head->tmp[i + 1], ERROR_DIR_MSG);
}
