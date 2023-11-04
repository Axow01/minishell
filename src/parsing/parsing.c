#include "minishell.h"
#include <stdio.h>
#include <string.h>

int	count_cmd_total(char *str, char delim)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == delim)
			{
				count++;
			}
		}
		i++;
	}
	return (count);
}

void	replace_space(char *str, size_t start, size_t end)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (ft_isspace(str[i]))
				str[i] = '\0';
		}
		i++;
	}
}

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

char	*setup_line(char *str, size_t *len)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	*len = count_redirection(str) + ft_strlen(str) + dollars_count(str) + 1;
	// printf("dollars_count: %zu\n", dollars_count(str));
	// printf("redir : %zu\n", count_redirection(line));
	// printf("stlen : %zu\n", ft_strlen(str));
	printf("stlen : %zu\n", *len);
	if (*len == 0)
		return (NULL);
	new_line = mms_alloc(*len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '$' && !isinquote(str, i, SINGLE_QUOTE))
		{
			// if (str[i] == '$' && str[i + 1] == '$' && !isinquote(str, i,
			// 		SINGLE_QUOTE))
			// {
			// 	new_line[j++] = '$';
			// 	i += 2;
			// }
			if (str[i] == '$' && !isinquote(str, i, SINGLE_QUOTE))
				dollars_token_copy(str, new_line, &i, &j);
		}
		if (str[i] && !isinquote(str, i, QUOTES))
		{
			if (str[i] == '|' && !isinquote(str, i, QUOTES))
			{
				new_line[j++] = ' ';
				new_line[j++] = str[i++];
				new_line[j++] = ' ';
			}
			while (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i],
					"<<", 2) == 0)
			{
				new_line[j++] = ' ';
				new_line[j++] = str[i++];
				new_line[j++] = str[i++];
				new_line[j++] = ' ';
			}
			if (str[i] == '>' || str[i] == '<')
			{
				new_line[j++] = ' ';
				new_line[j++] = str[i++];
				new_line[j++] = ' ';
			}
		}
		new_line[j++] = str[i++];
	}
	return (new_line);
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

size_t	count_token(char *line, size_t start, size_t end)
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

void	remove_quote(t_command *head)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*new;

	i = 0;
	while (head && head->tmp && head->tmp[i])
	{
		j = 0;
		k = 0;
		new = mms_alloc(ft_strlen(head->tmp[i]) + 1, sizeof(char));
		while (head->tmp[i][j])
		{
			if (!is_coated_quote(head->tmp[i], j))
				new[k++] = head->tmp[i][j];
			j++;
		}
		mms_free(head->tmp[i]);
		head->tmp[i] = new;
		i++;
	}
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
	int fd;

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
				fd = open(head->tmp[i + 1], O_CREAT | O_RDWR);
				head->stdout_ = fd;
			}
			else if (isredirec(head->tmp[i]) == 1 && head->tmp[i][0] == '<')
			{
				fd = open(head->tmp[i + 1], O_RDWR);
				head->stdin_ = fd;
			}
			else if (isredirec(head->tmp[i]) == 2 && head->tmp[i][0] == '>')
			{
				fd = open(head->tmp[i + 1], O_CREAT | O_APPEND | O_RDWR);
				head->stdout_ = fd;
			}
			printf("FD: %d\n", fd);
			if (fd < 0)
				break;
		}
		i++;
	}
	if (fd < 0)
		printf("minishell: %s: %s", head->tmp[i + 1], ERROR_DIR_MSG);
}

size_t count_nonerdt_token(char **token)
{
	size_t i;
	size_t count;

	i  = 0;
	count = 0;
	while (token && token[i])
	{
		if (isredirec(token[i]))
			i++;
		else 
			count ++;
		i++;
	}
	return (count);
}

void tmp_to_cmd(t_command *head)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	head->cmd = mms_alloc(count_nonerdt_token(head->tmp) + 1, sizeof(char *));
	while (head->tmp && head->tmp[i])
	{
		if (isredirec(head->tmp[i]))
			i++;
		else 
			head->cmd[j++] = head->tmp[i];
		i++;
	}
}

bool	cmd_maker(char *str, size_t len)
{
	size_t		i;
	size_t		end;
	size_t		start;
	t_command	*head;

	i = 0;
	start = 0;
	head = &get_infos()->cmd;
	while (i <= len)
	{
		if ((str[i] == '|' && !isinquote(str, i, QUOTES)) || i == len)
		{
			end = i;
			// printf("Start: %zu End: %zu\n", start, end);
			head->tmp = mms_alloc(count_token(str, start, end) + 1, sizeof(char *));
			head->stdin_ = STDIN_FILENO;
			head->stdout_ = STDOUT_FILENO;
			get_token(str, start, end, head);
			if (!head->tmp || !head->tmp[0] || !head->tmp[0][0])
				return (printf("%s`|'\n", ERROR_BASE_MSG), false);
			if (!check_valid_redirec(head))
				return (false);
			fd_maker(head);
			remove_quote(head);
			tmp_to_cmd(head);
			head = head->next;
			start = end + 1;
		}
		i++;
	}
	return (true);
}

void	parsing(char *line)
{
	char	*new;
	size_t	len;

	new = setup_line(line, &len);
	if (new == NULL)
		return ;
	init_cmd_struct(line);
	replace_space(new, 0, len);
	if (isinquote(line, ft_strlen(line) - 1, QUOTES))
		printf("%s(\"or')\n", ERROR_QUOTE_MSG);
	else if (cmd_maker(new, len))
	{
		// execution(get_infos());
		printf("%s\n", line);
		strnput(new, len);
		print_cmd(&get_infos()->cmd);
		// printf("len : %zu\n", len);
		printf("\n");
	}
	free_cmd(&get_infos()->cmd);
	new = mms_free(new);
}
